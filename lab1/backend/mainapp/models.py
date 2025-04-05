from django.db import models

# Create your models here.

class ProcessInstances(models.Model):
    process_name = models.CharField(max_length=50, null=True)
    state = models.CharField(max_length=20, null=True)
    update_time = models.DateTimeField(null=True)
    description = models.TextField(null=True)
    priority = models.IntegerField(null=True)

    def __str__(self):
        return f"ProcessInstance(process_name={self.process_name}, state={self.state})"