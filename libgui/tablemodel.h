/*
 * tablemodel.h
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Turbin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "gui_global.h"
#include "rowdata.h"
#include "messagehandler.h"
#include "querydb.h"
#include <QAbstractTableModel>

namespace LibGUI {

class GUISHARED_EXPORT TableModel: public QAbstractTableModel, public LibG::MessageHandler
{
    Q_OBJECT
public:
    enum PageStatus { None, Loading, Loaded };
    TableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void reset();
    void addColumn(const QString &key, const QString &title, const int &align = Qt::AlignLeft);
    inline void setTypeCommand(const int &type, const int &command) { mTypeCommand = std::make_tuple(type, command); }

public slots:
    void refresh();

protected:
    void messageReceived(LibG::Message *msg) override;

protected:
    int mNumRow;
    RowData mData;
    QList<QString> mHeaders;
    QList<QString> mColumns;
    QList<int> mAlignments;
    std::tuple<int, int> mTypeCommand;
    QMap<int, int> mPageStatus;
    bool mIsLoaded;
    LibDB::QueryDB mQuery;

signals:
    void loadMore(int page) const;
    void firstDataLoaded();

private slots:
    void loadPage(int page = 0);

private:
    void readData(LibG::Message *msg);
};

}
#endif // TABLEMODEL_H
