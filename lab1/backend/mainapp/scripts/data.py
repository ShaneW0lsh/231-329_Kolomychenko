import random

from datetime import timedelta
from django.utils import timezone
from mainapp.models import ProcessInstances

def run():
    states = ['PENDING', 'ACTIVE', 'COMPLETED', 'ABORTED', 'SUSPENDED']
    entries = []
    for i in range(1000):
        entry = ProcessInstances(
            process_name=f"Process {i+1}",
            state=random.choice(states),
            update_time=timezone.now() - timedelta(days=random.randint(0, 365)),
            description=f"Description for process {i+1}",
            priority=random.randint(0, 10)
        )
        entries.append(entry)

    ProcessInstances.objects.bulk_create(entries)
    print("Successfully inserted 1000 entries")
