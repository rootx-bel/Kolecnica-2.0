# Generated by Django 4.1.1 on 2022-10-09 09:42

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0006_route_geom_keypointsplaned'),
    ]

    operations = [
        migrations.AddField(
            model_name='geom',
            name='date',
            field=models.DateField(auto_now_add=True, default=django.utils.timezone.now),
            preserve_default=False,
        ),
    ]
