# -*- mode: python -*-

block_cipher = None


a = Analysis(['gui.py'],
             pathex=['/Users/t_waugs/Documents/Objeus repo/soul/creator'],
             binaries=None,
             datas=None,
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher)
a.datas += [('icon.gif','/Users/t_waugs/Documents/Objeus repo/soul/creator/icon.gif','DATA')]
a.datas += [('creator_logo.png','/Users/t_waugs/Documents/Objeus repo/soul/creator/creator_logo.png','DATA')]
a.datas += [('lib/arcanaDescription.json','/Users/t_waugs/Documents/Objeus repo/soul/creator/lib/arcanaDescription.json','DATA')]
a.datas += [('lib/data.json','/Users/t_waugs/Documents/Objeus repo/soul/creator/lib/data.json','DATA')]

pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          exclude_binaries=True,
          name='gui',
          debug=False,
          strip=False,
          upx=True,
          console=False )
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               name='gui')
app = BUNDLE(coll,
             name='Story Creator.app',
             icon='/Users/t_waugs/Documents/Objeus repo/soul/creator/icon.icns',
             bundle_identifier=None)
