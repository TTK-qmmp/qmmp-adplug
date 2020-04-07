/* =================================================
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2020 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include "adplugmetadatamodel.h"
#include "adplughelper.h"

AdplugMetaDataModel::AdplugMetaDataModel(const QString &path)
    : MetaDataModel(true)
{
    AdplugHelper helper(path.toUtf8().constData());
    if(helper.initialize())
    {
        fill_in_extra_properties(&helper);
        fill_in_descriptions(&helper);
    }
}

void AdplugMetaDataModel::fill_in_extra_properties(AdplugHelper *helper)
{
    if(helper->instrument_count() != 0)
    {
        QString text;
        for(const std::string &s : helper->instruments())
        {
            text += QString::fromStdString(s) + "\n";
        }
        m_desc << MetaDataItem(tr("Instruments"), text);
    }
}

void AdplugMetaDataModel::fill_in_descriptions(AdplugHelper *helper)
{
    m_ap << MetaDataItem(tr("Title"), QString::fromStdString(helper->title()));
    m_ap << MetaDataItem(tr("Format"), QString::fromStdString(helper->format()));
    m_ap << MetaDataItem(tr("Author"), QString::fromStdString(helper->author()));
    m_ap << MetaDataItem(tr("Description"), QString::fromStdString(helper->author()));

    if(helper->pattern_count() != 0)
    {
        m_ap << MetaDataItem(tr("Patterns"), QString::number(helper->pattern_count()));
    }
    if(helper->instrument_count() != 0)
    {
        m_ap << MetaDataItem(tr("Instruments"), QString::number(helper->instrument_count()));
    }
}

QList<MetaDataItem> AdplugMetaDataModel::extraProperties() const
{
    return m_ap;
}

QList<MetaDataItem> AdplugMetaDataModel::descriptions() const
{
    return m_desc;
}
