from shotgun_api3 import Shotgun
import os

SCRIPT_NAME = 'Samuel - API'
SCRIPT_KEY = '2b3f3b6e442242c067501a9e17503bac1d27b6ea244a4e4b5987e26d5f6520e2'
sg = Shotgun("https://objeus.shotgunstudio.com", SCRIPT_NAME, SCRIPT_KEY)

epers = sg.find('Attachment', [['attachment_links', 'type_is', 'CustomEntity07']], ['attachment_links'])
for eper in epers:
	sg.download_attachment(eper, os.path.abspath(os.path.expanduser("importdata/" + eper['attachment_links'][0]['name'] + ".json")))
