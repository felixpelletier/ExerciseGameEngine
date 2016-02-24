import sys
from PyQt4.QtGui import QApplication, QMessageBox
 
 

# Create an PyQT4 application object.
a = QApplication(sys.argv)       
""" 
# The QWidget widget is the base class of all user interface objects in PyQt4.
w = QWidget()
# Set window size. 
w.resize(320, 240)
# Set window title  
w.setWindowTitle("Hello World!") 
# Show window
w.show() 
 
sys.exit(a.exec_())
"""

# Show a message box
result = QMessageBox.question(None, 'Message', "Do you like Python?", QMessageBox.Yes | QMessageBox.No)
if result == QMessageBox.Yes:
    print 'Yes.'
else:
    print 'No.' 