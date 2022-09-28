from django.shortcuts import render
from django.contrib.auth.models import User
from .models import Geom

def index(request):
    #return HttpResponse("I hate django")
    return render(request, 'main/index.html')

def map(request):
    return render(request, 'main/map.html')

def geo(request):
    data = Geom.objects.all()
    return render(request, 'main/geo.html', {'data': data})