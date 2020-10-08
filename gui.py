#!/usr/bin/python3
import sys
from subprocess import Popen
from PyQt5.QtWidgets import (
	QApplication, QWidget, QPushButton, QLineEdit,
	QLCDNumber, QGridLayout, QLabel, QMessageBox,
	QProgressBar, QComboBox, QStatusBar, QSlider
	)
from PyQt5.QtGui import (
	QIcon, QPixmap
	)
from PyQt5.QtCore import (
	Qt
	)


class FillerUI(QWidget):
	def __init__(self):
		super().__init__()
		self.initUI()
		self.place()

	def initUI(self):
		self.resize(800, 800)
		self.setWindowTitle('Filler')
		self.setWindowIcon(QIcon('icon.png'))
		self.okButton = QPushButton()
		self.okButton.setText('OK')
		self.okButton.clicked.connect(self.go)
		self.WLCD = QLCDNumber()
		self.WLCD.display(1200)
		self.HLCD = QLCDNumber()
		self.HLCD.display(1200)
		self.PLCD = QLCDNumber()
		self.PLCD.display(100)
		self.WSlide = QSlider(Qt.Horizontal)
		self.WSlide.setRange(100, 3000)
		self.WSlide.setValue(1200)
		self.HSlide = QSlider(Qt.Horizontal)
		self.HSlide.setRange(100, 3000)
		self.HSlide.setValue(1200)
		self.PSlide = QSlider(Qt.Horizontal)
		self.PSlide.setRange(1, 1000)
		self.PSlide.setValue(100)
		self.WSlide.valueChanged.connect(self.WLCD.display)
		self.HSlide.valueChanged.connect(self.HLCD.display)
		self.PSlide.valueChanged.connect(self.PLCD.display)
		self.WLabel = QLabel()
		self.WLabel.setText('Ширина окна в пикселях:')
		self.HLabel = QLabel()
		self.HLabel.setText('Высота окна в пикселях:')
		self.PLabel = QLabel()
		self.PLabel.setText('Пикселей на единичный отрезок:')

	def place(self):
		self.grid = QGridLayout()
		self.grid.setSpacing(5)
		self.grid.addWidget(self.WLabel, 0, 0, 2, 1)
		self.grid.addWidget(self.WLCD, 0, 1, 1, 1)
		self.grid.addWidget(self.WSlide, 1, 1, 1, 1)
		self.grid.addWidget(self.HLabel, 2, 0, 2, 1)
		self.grid.addWidget(self.HLCD, 2, 1, 1, 1)
		self.grid.addWidget(self.HSlide, 3, 1, 1, 1)
		self.grid.addWidget(self.PLabel, 4, 0, 2, 1)
		self.grid.addWidget(self.PLCD, 4, 1, 1, 1)
		self.grid.addWidget(self.PSlide, 5, 1, 1, 1)
		self.grid.addWidget(self.okButton, 6, 0, 1, 2)
		self.setLayout(self.grid)

	def go(self):
		W = int(self.WLCD.value())
		H = int(self.HLCD.value())
		P = int(self.PLCD.value())
		with open('consts.conf', 'w') as file:
			print(W, file=file)
			print(H, file=file)
			print(P, file=file)
			file.close()
		Popen('./a.out')
#		exit()


if __name__ == '__main__':
	app = QApplication(sys.argv)
	ex = FillerUI()
	ex.show()
	sys.exit(app.exec())