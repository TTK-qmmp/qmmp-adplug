/***************************************************************************
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2022 Greedysky Studio

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
 ***************************************************************************/

#ifndef DECODER_ADPLUG_H
#define DECODER_ADPLUG_H

#include <qmmp/decoder.h>

class AdplugHelper;

/*!
 * @author Greedysky <greedysky@163.com>
 */
class DecoderAdplug : public Decoder
{
public:
    explicit DecoderAdplug(const QString &path);
    virtual ~DecoderAdplug();

    virtual bool initialize() override final;
    virtual qint64 totalTime() const override final;
    virtual int bitrate() const override final;
    virtual qint64 read(unsigned char *data, qint64 maxSize) override final;
    virtual void seek(qint64 time) override final;

private:
    qint64 copy(unsigned char *data, qint64 maxSize);

    AdplugHelper *m_helper = nullptr;
    unsigned char *m_bufptr = nullptr;
    qint64 m_buf_filled = 0;
    unsigned long m_time = 0;
    unsigned long m_length = 0;
    double m_divisor = 0.0;

};

#endif
