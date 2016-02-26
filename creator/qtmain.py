from PyQt4.QtGui import QApplication, QWidget
import sys
from qtgui import MainFrame

app = QApplication(sys.argv)

#Call to qtgui.py here
m = MainFrame()

sys.exit(app.exec_())