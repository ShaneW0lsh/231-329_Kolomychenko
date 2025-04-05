from rest_framework import serializers

from .models import ProcessInstances

class ProcessInstanceSerializer(serializers.ModelSerializer):

    class Meta:
        model = ProcessInstances
        fields = "__all__"