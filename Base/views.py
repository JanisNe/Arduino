from django.http import HttpResponse
from django.shortcuts import render

from .models import *

# Create your views here.

def main(request):
    context = {
        "rooms": Room.objects.all(),
    }
    return render(request, "Base/main.html", context)

def readData(request, room, temperature, humidity):

    added_data = RoomData(
        room = Room.objects.get_or_create(room=room)[0],
        temperature = temperature,
        humidity = humidity
    )
    added_data.save()

    return HttpResponse("Success")

def update(request):
    context = {
        "rooms": Room.objects.all(),
    }
    return render(request, "Base/update.html", context)