from django.shortcuts import render
from .models import Geom, Route
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
        target = target.split(',')
        data = Route.objects.get(ids=0)
        data.points = ''
        flag = False
        for i in target:
            if not flag:
                data.points += i + '&'
                flag = True
            else:
                data.points += i + ';'
                flag = False
        data.points = data.points[:-1]
        data.save()
        print(data.points)
        return HttpResponse()
    elif request.method == 'GET' and request.GET.get('points') is not None:
        points = request.GET.get('points')
        temp = request.GET.get('temp')
        idds = request.GET.get('idds')
        te = Geom.objects.get(ids=int(idds))
        coords = points.split(',')
        if te.numpointspl == 0:
            te.keypoints = ''
            te.keypoints = coords[0]+"&"+coords[1]+'&'+temp+';'
            te.numpoints = te.numpoints + 1
            te.save()
        elif te.numpointspl - 1 == te.numpoints:
            te.keypoints = te.keypoints+coords[0]+"&"+coords[1]+'&'+temp
            te.numpoints = te.numpoints + 1
            te.save()
            data = Route.objects.get(ids=0)
            data.points = ''
            data.save()
        else:
            te.keypoints = te.keypoints+coords[0]+"&"+coords[1]+'&'+temp+';'
            te.numpoints = te.numpoints + 1
            te.save()
        return HttpResponse(points+" "+temp+" "+idds)
    elif request.method == 'GET' and request.GET.get('start') is not None:
        data = Route.objects.get(ids=0)
        iddata = Geom.objects.latest('ids')
        num = int(iddata.ids) + 1
        x = data.points.split(';')
        Geom.objects.create(ids=num, keypointsplaned = str(data.points), numpointspl = len(x))
        return HttpResponse(data.points+"*"+str(num))
        