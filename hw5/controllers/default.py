# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

from gluon import utils as gluon_utils
import random
import json
import time

def index() :
    redirect(URL('default', 'boards'))

def boards():
    return {}

def board() :
    board = db.boards(request.args(0))
    return {"board_id":request.args(0)}

from gluon.contrib.populate import populate

def populatedb() :
    populate(db.auth_user,2)
    populate(db.boards,3)
    populate(db.posts,12)
    boards = db(db.boards).select(orderby=db.boards.updated_at) 
    redirect(URL('default', 'boards'))

def deletedb() :
    db.posts.truncate()
    db.boards.truncate()
    # db.auth_user.truncate()
    redirect(URL('default', 'boards'))

def home() :
    redirect(URL('default', 'boards'))

def do_logout() :
    redirect(URL('default', 'user', args=['logout']))

def do_login() :
    redirect(URL('default', 'user', args=['login']))

def do_register() :
    redirect(URL('default', 'user', args=['register']))

@auth.requires_signature()
def add_post():
    post = db(db.posts.post_id == request.vars.post_id).select().first()
    board = db(db.boards.id == request.vars.board).select().first()
    if post :
        post.update_record(
            title=request.vars.title,
            dtitle=request.vars.dtitle,
            board=board,
            body=request.vars.body,
            dbody=request.vars.dbody,
            author= request.vars.author,
            is_draft=json.loads(request.vars.is_draft)
        )
        return post #load_post(request.vars.board_id);

    db['posts'].insert(
        title=request.vars.title,
        dtitle=request.vars.dtitle,
        board=board,
        body=request.vars.body,
        dbody=request.vars.dbody,
        author= request.vars.author,
        is_draft=json.loads(request.vars.is_draft)
    )
    return post #load_post(request.vars.board_id);

@auth.requires_signature()
def add_board():
    board = db(db.boards.board_id == request.vars.board_id).select().first()
    if board :
        board.update_record(
            title=request.vars.title,
            dtitle=request.vars.dtitle,
            board_id=str(request.vars.board_id),
            description=request.vars.description,
            ddescription=request.vars.ddescription,
            creator = request.vars.creator,
            is_draft=json.loads(request.vars.is_draft)
        )
        return load_board(request.vars.board_id);

    db['boards'].insert(
            title=request.vars.title,
            dtitle=request.vars.dtitle,
            board_id=str(request.vars.board_id),
            description=request.vars.description,
            ddescription=request.vars.ddescription,
            creator = request.vars.creator,
            is_draft=json.loads(request.vars.is_draft)
            )
    return load_board(request.vars.board_id);

@auth.requires_signature()
def remove_post():
    return db(db.posts.post_id == request.vars.post_id).delete()

@auth.requires_signature()
def remove_board():
    if not auth.user_id : return False

    if(auth.user_id != db(db.boards.board_id == request.vars.board_id).select.first().creator) :
        return False
    return db(db.boards.board_id == request.vars.board_id).delete()


@auth.requires_signature()
def add_favorite():
    user_id = auth.user_id
    board_id = request.vars.board_id
    db.boards.update_or_insert((db.pinned_boards.user_id == user and db.pinned_boards.board_id == board_id),
            board_id=board_id,
            user_id=user_id)
    return True

def load_board():
    return load_board(request.vars.board_id);

def load_board(board_id) :
    """Loads One Board, just the board"""
    board = db(db.boards.board_id == board_id).select().first()

    board_dict = {
                  "board_id" : board.board_id,
                  "creator" : board.creator,
                  "title"    : board.title,
                  "dtitle"    : board.dtitle,
                  "num_posts" : db(db.posts.board == board).count(),
                  "description" : board.description,
                  "ddescription" : board.ddescription,
                  "created_at" : board.created_at.isoformat(),
                  "is_draft" : board.is_draft,
                  "uri" : URL('default', 'board', args=[str(board.id)])
                  }

    return response.json(dict(
                             board_dict= board_dict
                         ))

def load_posts():
    ret =load_posts_internal(request.vars.board_id);
    return ret

def load_posts_internal(board_id) :
    """Loads One Board and all the posts for that board"""
    board = db(db.boards.id == board_id).select().first()
    posts = db(db.posts.board == board_id).select(orderby=~db.posts.created_at)

    my_posts = []
    if auth.user and auth.user_id :
        my_posts = [b for b in posts if b.author == auth.user_id]

    board_dict = {
                  "board_id" : board.board_id,
                  "creator" : board.creator,
                  "title"    : board.title,
                  "dtitle"    : board.dtitle,
                  "num_posts" : db(db.posts.board == board).count(),
                  "description" : board.description,
                  "ddescription" : board.ddescription,
                  "created_at" : board.created_at.isoformat(),
                  "is_draft" : board.is_draft,
                  "uri" : URL('default', 'board', args=[str(board.id)])
                  }

    return response.json(dict(
                             board_dict= board_dict,
                             post_list = posts,
                             user_id = (auth.user_id if auth and auth.user else -1)
                         ))

def load_boards():
    """Loads all boards for the user."""
    boards = db(db.boards).select(orderby=~db.boards.updated_at) 
    my_boards = []
    if auth.user and auth.user_id :
        my_boards = [b for b in boards if b.creator == auth.user_id]

    board_list = [
            {
              "board_id" : r.board_id,
              "creator" : r.creator,
              "title"    : r.title,
              "dtitle"    : r.dtitle,
              "num_posts" : db(db.posts.board == r).count(),
              "description" : r.description,
              "ddescription" : r.ddescription,
              "created_at" : r.created_at.isoformat(),
              "is_draft" : r.is_draft,
              "uri" : URL('default', 'board', args=[str(r.id)])
            }
            for r in boards]

    my_boards = [ {"title" : r.title,
                  "uri" : URL('default', 'board', args=[str(r.id)])}
                for r in my_boards ]

    return response.json(dict(
                             board_list=board_list,
                             my_boards=my_boards,
                             user_id = (auth.user_id if auth and auth.user else -1)
                         ))

def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    http://..../[app]/default/user/manage_users (requires membership in
    http://..../[app]/default/user/bulk_register
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    """
    return dict(form=auth())


@cache.action()
def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()


