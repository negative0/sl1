#!/bin/bash
curl http://login.secureunibox.com/portals/pict/index.php
url='http://login.secureunibox.com/onboardPortalEngine/uniboxlogin.php'
curl POST --data "{ 'mobileno'='9552565839','passwd'='chaitanya071098','button'='Login' }" $url
