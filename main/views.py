from django.shortcuts import render
from django.http import HttpResponse
from django.contrib.auth.models import User

def index(request):
    #return HttpResponse("I hate django")
    return render(request, 'main/index.html')