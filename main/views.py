from django.shortcuts import render
from .models import Geom
import json
from django.http import HttpResponse

def index(request):
    #return HttpResponse("I hate django")
    return render(request, 'main/index.html')

def map(request):
    return render(request, 'main/map.html')

def geo(request):
    if request.method == 'GET' and request.GET.get('ids') is not None:
        idnum = int(request.GET.get('ids'))
        data = Geom.objects.get(ids=idnum)
        return HttpResponse(data.keypoints+"*"+data.keypointsplaned)
    else:
        data = Geom.objects.all()
        return render(request, 'main/geo.html', {'data': data})