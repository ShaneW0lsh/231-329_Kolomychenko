from django.shortcuts import render

from django.conf import settings

from rest_framework import viewsets

from .models import ProcessInstances
from .serializers import ProcessInstanceSerializer

class ProcessInstanceViewSet(viewsets.ModelViewSet):
    queryset = ProcessInstances.objects.filter(id__lte=10)
    serializer_class = ProcessInstanceSerializer

