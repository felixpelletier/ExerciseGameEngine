from shotgun_api3 import Shotgun
import os

SCRIPT_NAME = 'Samuel - API'
SCRIPT_KEY = '2b3f3b6e442242c067501a9e17503bac1d27b6ea244a4e4b5987e26d5f6520e2'
sg = Shotgun("https://objeus.shotgunstudio.com", SCRIPT_NAME, SCRIPT_KEY)

echars = sg.find('Attachment', [['attachment_links', 'type_is', 'CustomEntity06']], ['attachment_links'])
for echar in echars:
	sg.download_attachment(echar, os.path.abspath(os.path.expanduser("importdata/" + echar['attachment_links'][0]['name'] + ".json")))
