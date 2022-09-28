from django.db import models

class Geom(models.Model):
    ids = models.IntegerField(default=0, name="ids")
    keypoints = models.TextField(max_length=20000, name="keypoints", default="")
    ids = models.IntegerField(default=0)
    
    def __str__(self):
        return str(self.ids)

    class Meta:
        verbose_name = "История"
        verbose_name_plural = "История"

class Flags(models.Model):
    title = models.CharField(max_length=255)
    keypoint = models.BooleanField()
    
    def __str__(self):
        return self.title

    class Meta:
        verbose_name = "Флаги"
        verbose_name_plural = "Флаги"