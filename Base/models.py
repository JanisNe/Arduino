from django.db import models

# Create your models here.

class Room(models.Model):
    room = models.CharField(max_length=100)

    def __str__(self):
        return self.room

    def reverse(self):
        return RoomData.objects.filter(room=self).order_by("-id")[:20]

class RoomData(models.Model):
    room = models.ForeignKey(Room, on_delete=models.CASCADE, related_name="room_data")
    temperature = models.FloatField(default=None, null=True)
    humidity = models.FloatField(default=None, null=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.room.room + " " + str(self.temperature) + " " + str(self.humidity)

