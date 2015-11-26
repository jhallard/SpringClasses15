#########################################################################
## Define your tables below; for example
##
## >>> db.define_table('mytable',Field('myfield','string'))
##
## Fields can be 'string','text','password','integer','double','boolean'
##       'date','time','datetime','blob','upload', 'reference TABLENAME'
## There is an implicit 'id integer autoincrement' field
## Consult manual for more options, validators, etc.
##
## More API examples for controllers:
##
## >>> db.mytable.insert(myfield='value')
## >>> rows=db(db.mytable.myfield=='value').select(db.mytable.ALL)
## >>> for row in rows: print row.id, row.myfield
#########################################################################

import datetime
import uuid


db.define_table('boards',
          Field('creator', db.auth_user, default=auth.user_id),
          Field('title', 'string'),
          Field('dtitle', 'string'),
          Field('board_id', 'string'),
          Field('description', 'string'),
          Field('ddescription', 'string'),
          Field('created_at', 'datetime', default=datetime.datetime.now(), readable=False, writable=False),
          Field('is_draft', 'boolean', default=False), 
          Field('updated_at', 'datetime', readable=False, writable=False))

db.define_table('posts',
          Field('author', db.auth_user, default=auth.user_id),
          Field('board', 'reference boards', readable=False, writable=False),
          Field('created_at', 'datetime', default=datetime.datetime.now(), readable=False, writable=False),
          Field('title', 'string'),
          Field('post_id', 'string', default=str(uuid.uuid4())),
          Field('is_draft', 'boolean', default=False),
          Field('body', 'text'))

db.define_table('pinned_boards',
          Field('user_id', db.auth_user, default=auth.user_id),
          Field('board_id', db.boards))
