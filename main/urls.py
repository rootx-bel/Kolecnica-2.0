from django.contrib.auth import views
from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='home'),
]