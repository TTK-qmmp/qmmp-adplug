#include "decoderadplugfactory.h"
#include "adplughelper.h"
#include "decoder_adplug.h"
#include "adplugmetadatamodel.h"

#include <QMessageBox>

bool DecoderAdplugFactory::canDecode(QIODevice *input) const
{
    QFile *file = static_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    AdplugHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderAdplugFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("AdPlug Plugin");
    properties.shortName = "adplug";
    properties.filters << "*.a2m" << "*.adl" << "*.adlib" << "*.agd" << "*.amd" << "*.as3m";
    properties.filters << "*.bam" << "*.bmf";
    properties.filters << "*.cff" << "*.cmf";
    properties.filters << "*.d00" << "*.dfm" << "*.dmo" << "*.dro" << "*.dtm";
    properties.filters << "*.got";
    properties.filters << "*.ha2" << "*.hsc" << "*.hsq" << "*.hsp";
    properties.filters << "*.imf" << "*.ims";
    properties.filters << "*.jbm";
    properties.filters << "*.ksm";
    properties.filters << "*.laa" << "*.lds";
    properties.filters << "*.m" << "*.mad" << "*.mdi" << "*.mkj" << "*.msc" << "*.mtk" << "*.mus";
    properties.filters << "*.rac" << "*.rad" << "*.raw" << "*.rix" << "*.rol";
    properties.filters << "*.s3m" << "*.sa2" << "*.sat" << "*.sci" << "*.sdb" << "*.sng" << "*.sop" << "*.sqx";
    properties.filters << "*.xad" << "*.xms" << "*.xsm";
    properties.filters << "*.vgm" << "*.vgz";
    properties.filters << "*.wlf";
    properties.description = "AdLib Sound File";
    properties.protocols << "file";
    properties.noInput = true;
    return properties;
}

Decoder *DecoderAdplugFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderAdplug(path);
}

QList<TrackInfo*> DecoderAdplugFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    AdplugHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::MetaData)
    {
        info->setValue(Qmmp::TITLE, helper.title());
        info->setValue(Qmmp::ARTIST, helper.author());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "AdLib Sound");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel *DecoderAdplugFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(readOnly);
    return new AdplugMetaDataModel(path);
}

void DecoderAdplugFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderAdplugFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About Adplug Reader Plugin"),
                       tr("Qmmp Adplug Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderAdplugFactory::translation() const
{
    return QString();
}
