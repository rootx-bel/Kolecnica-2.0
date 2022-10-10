from django.shortcuts import render
from .models import Geom
from django.http import HttpResponse
from django.contrib.auth.decorators import login_required

def index(request):
    #return HttpResponse("I hate django")
    return render(request, 'main/index.html')

@login_required(login_url='home')
def map(request):
    return render(request, 'main/map.html')

@login_required(login_url='home')
def geo(request):
    if request.method == 'GET' and request.GET.get('ids') is not None:
        idnum = int(request.GET.get('ids'))
        data = Geom.objects.get(ids=idnum)
        return HttpResponse(data.keypoints+"*"+data.keypointsplaned)
    else:
        data = Geom.objects.all()
        return render(request, 'main/geo.html', {'data': data})

def communicate(request):
    # return HttpResponse('You lox')
    if request.method == 'GET' and request.GET.get('keys') is not None:
        target = request.GET.get('keys')
        print(target)
        # data = Geom.objects.get(ids=idnum)
        # return HttpResponse(data.keypoints+"*"+data.keypointsplaned)
    elif request.method == 'GET' and request.GET.get('points') is not None:
        points = request.GET.get('points')
        # data = Geom.objects.get(ids=idnum)
        # return HttpResponse(data.keypoints+"*"+data.keypointsplaned)