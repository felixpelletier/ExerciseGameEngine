from PyQt4.QtGui import QApplication, QWidget, QIcon
import sys
import json_reader
from qtmainframe import MainFrame

app = QApplication(sys.argv)
app.setWindowIcon(QIcon(json_reader.buildPath('icon.gif')))
m = MainFrame(app)
sys.exit(app.exec_())