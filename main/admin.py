from django.contrib import admin
from .models import Geom, Flags, Route

admin.site.register(Geom)
admin.site.register(Flags)
admin.site.register(Route)