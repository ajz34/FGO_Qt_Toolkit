/*
* This file has been changed by ajz34 for fgo purpose
*/

/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "xml_editable_mainwindow.h"

#include <QFile>

xml_editable_mainwindow::xml_editable_mainwindow(QString file_path_transin, QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);

	QStringList headers;
	headers << tr("Name") << tr("Type") << tr("Value");

	file_path = file_path_transin;
	QFile file(file_path);
	file.open(QFile::ReadOnly | QFile::Text);
	QXmlStreamReader xml;
	xml.setDevice(&file);
	model = new TreeModel(headers, xml);
	file.close();

	view->setModel(model);
	// for (int column = 0; column < model->columnCount(); ++column)
	//     view->resizeColumnToContents(column);
	view->setColumnWidth(0, QLabel(QString("consume_rarityconsume_rarity      ")).sizeHint().width());
	view->setColumnWidth(1, QLabel(QString("dict      ")).sizeHint().width());
	view->setColumnWidth(2, QLabel(QString("ジャンヌ・ダルク・オルタ・サンタ・リリィ      ")).sizeHint().width());

	connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

	connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
		this, &xml_editable_mainwindow::updateActions);

	connect(actionsMenu, &QMenu::aboutToShow, this, &xml_editable_mainwindow::updateActions);
	connect(insertRowAction, &QAction::triggered, this, &xml_editable_mainwindow::insertRow);
	// connect(insertColumnAction, &QAction::triggered, this, &MainWindow::insertColumn);
	connect(removeRowAction, &QAction::triggered, this, &xml_editable_mainwindow::removeRow);
	// connect(removeColumnAction, &QAction::triggered, this, &MainWindow::removeColumn);
	connect(insertChildAction, &QAction::triggered, this, &xml_editable_mainwindow::insertChild);
	connect(saveAction, &QAction::triggered, this, &xml_editable_mainwindow::saveFile);

	updateActions();
}

void xml_editable_mainwindow::insertChild()
{
	QModelIndex index = view->selectionModel()->currentIndex();
	QAbstractItemModel *model = view->model();

	if (model->columnCount(index) == 0) {
		if (!model->insertColumn(0, index))
			return;
	}

	if (!model->insertRow(0, index))
		return;

	for (int column = 0; column < model->columnCount(index); ++column) {
		QModelIndex child = model->index(0, column, index);
		model->setData(child, QVariant("[No data]"), Qt::EditRole);
		if (!model->headerData(column, Qt::Horizontal).isValid())
			model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
	}

	view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
		QItemSelectionModel::ClearAndSelect);
	updateActions();
}

/* bool MainWindow::insertColumn()
{
QAbstractItemModel *model = view->model();
int column = view->selectionModel()->currentIndex().column();

// Insert a column in the parent item.
bool changed = model->insertColumn(column + 1);
if (changed)
model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

updateActions();

return changed;
} */

void xml_editable_mainwindow::insertRow()
{
	QModelIndex index = view->selectionModel()->currentIndex();
	QAbstractItemModel *model = view->model();

	if (!model->insertRow(index.row() + 1, index.parent()))
		return;

	updateActions();

	for (int column = 0; column < model->columnCount(index.parent()); ++column) {
		QModelIndex child = model->index(index.row() + 1, column, index.parent());
		model->setData(child, QVariant("[No data]"), Qt::EditRole);
	}
}

/* bool MainWindow::removeColumn()
{
QAbstractItemModel *model = view->model();
int column = view->selectionModel()->currentIndex().column();

// Insert columns in each child of the parent item.
bool changed = model->removeColumn(column);

if (changed)
updateActions();

return changed;
} */

void xml_editable_mainwindow::removeRow()
{
	QModelIndex index = view->selectionModel()->currentIndex();
	QAbstractItemModel *model = view->model();
	if (model->removeRow(index.row(), index.parent()))
		updateActions();
}

void xml_editable_mainwindow::saveFile()
{
	QFile file(file_path);
	file.open(QIODevice::WriteOnly | QFile::Text);
	QXmlStreamWriter xml;
	xml.setDevice(&file);
	xml.setAutoFormatting(true);
	xml.writeStartDocument();
	model->xml_write(xml);
	xml.writeEndDocument();
	statusBar()->showMessage("File Saved", 3000);
}

void xml_editable_mainwindow::updateActions()
{
	bool hasSelection = !view->selectionModel()->selection().isEmpty();
	removeRowAction->setEnabled(hasSelection);
	removeColumnAction->setEnabled(hasSelection);

	bool hasCurrent = view->selectionModel()->currentIndex().isValid();
	insertRowAction->setEnabled(hasCurrent);
	insertColumnAction->setEnabled(hasCurrent);

	if (hasCurrent) {
		view->closePersistentEditor(view->selectionModel()->currentIndex());

		int row = view->selectionModel()->currentIndex().row();
		int column = view->selectionModel()->currentIndex().column();
		if (view->selectionModel()->currentIndex().parent().isValid())
			statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
		else
			statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
	}
}
