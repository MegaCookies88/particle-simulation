TEMPLATE = subdirs

SUBDIRS += \
   general \
   Qt_GL \
   text

text.depends  = general

Qt_GL.depends = general
