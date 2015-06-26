#include "media.h"

#include "proofnetwork/jdf/data/qmlwrappers/mediaqmlwrapper.h"
#include "proofnetwork/jdf/data/medialink.h"
#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

namespace Proof {
namespace Jdf {

class MediaPrivate : AbstractPhysicalResourcePrivate
{
    Q_DECLARE_PUBLIC(Media)

    MediaPrivate() : AbstractPhysicalResourcePrivate(ApiHelper::ResourceClass::ConsumableClass) {}

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    double thickness = 0.0;
    double height = 0.0;
    double width = 0.0;
    ApiHelper::CoatingType frontCoating = ApiHelper::CoatingType::NoneCoating;
    ApiHelper::CoatingType backCoating = ApiHelper::CoatingType::NoneCoating;
    ApiHelper::MediaUnit mediaUnit = ApiHelper::MediaUnit::SheetMediaUnit;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

double Media::thickness() const
{
    Q_D(const Media);
    return d->thickness;
}

ApiHelper::CoatingType Media::frontCoating() const
{
    Q_D(const Media);
    return d->frontCoating;
}

ApiHelper::CoatingType Media::backCoating() const
{
    Q_D(const Media);
    return d->backCoating;
}

ApiHelper::MediaUnit Media::mediaUnit() const
{
    Q_D(const Media);
    return d->mediaUnit;
}

double Media::height() const
{
    Q_D(const Media);
    return d->height;
}

double Media::width() const
{
    Q_D(const Media);
    return d->width;
}

void Media::setThickness(double microns)
{
    Q_D(Media);
    if (d->thickness != microns) {
        d->thickness = microns;
        emit thicknessChanged(d->thickness);
    }
}

void Media::setFrontCoating(ApiHelper::CoatingType coating)
{
    Q_D(Media);
    if (d->frontCoating != coating) {
        d->frontCoating = coating;
        emit frontCoatingChanged(coating);
    }
}

void Media::setBackCoating(ApiHelper::CoatingType coating)
{
    Q_D(Media);
    if (d->backCoating != coating) {
        d->backCoating = coating;
        emit backCoatingChanged(coating);
    }
}

void Media::setMediaUnit(ApiHelper::MediaUnit mediaUnit)
{
    Q_D(Media);
    if (d->mediaUnit != mediaUnit) {
        d->mediaUnit = mediaUnit;
        emit mediaUnitChanged(mediaUnit);
    }
}

void Media::setHeight(double arg)
{
    Q_D(Media);
    if (d->height != arg) {
        d->height = arg;
        emit heightChanged(d->height);
    }
}

void Media::setWidth(double arg)
{
    Q_D(Media);
    if (d->width != arg) {
        d->width = arg;
        emit widthChanged(d->width);
    }
}

MediaQmlWrapper *Media::toQmlWrapper(QObject *parent) const
{
    Q_D(const Media);
    MediaSP castedSelf = qSharedPointerCast<Media>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new MediaQmlWrapper(castedSelf, parent);
}

MediaSP Media::create()
{
    MediaSP result(new Media());
    makeWeakSelf(result);
    return result;
}

MediaSP Media::fromJdf(QXmlStreamReader &xmlReader)
{
    MediaSP media = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Media" && xmlReader.isStartElement() && !media->isFetched()) {
            media->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            media->setId(attributes.value("ID").toString());
            media->setBackCoating(ApiHelper::coatingFromString(attributes.value("BackCoatings").toString()));
            media->setFrontCoating(ApiHelper::coatingFromString(attributes.value("FrontCoatings").toString()));
            media->setMediaUnit(ApiHelper::mediaUnitFromString(attributes.value("MediaUnit").toString()));
            media->setThickness(attributes.value("Thickness").toDouble());
            QStringList dimensions = attributes.value("Dimension").toString().split(' ', QString::SkipEmptyParts);
            if (dimensions.size() >= 2) {
                media->setWidth(dimensions[0].toDouble());
                media->setHeight(dimensions[1].toDouble());
            }

            AbstractPhysicalResourceSP castedMedia = qSharedPointerCast<AbstractPhysicalResource>(media);
            AbstractPhysicalResource::fromJdf(xmlReader, castedMedia);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return media;
}

void Media::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Media);
    jdfWriter.writeStartElement("Media");
    if (!qFuzzyCompare(1.0 + d->width, 1.0) || !qFuzzyCompare(1.0 + d->height, 1.0))
        jdfWriter.writeAttribute("Dimension", QString("%1 %2").arg(d->width, 0, 'f', 4).arg(d->height, 0, 'f', 4));
    jdfWriter.writeAttribute("BackCoatings", ApiHelper::coatingToString(d->backCoating));
    jdfWriter.writeAttribute("FrontCoatings", ApiHelper::coatingToString(d->frontCoating));
    jdfWriter.writeAttribute("MediaUnit", ApiHelper::mediaUnitToString(d->mediaUnit));
    jdfWriter.writeAttribute("Thickness", QString::number(d->thickness,'f', 4));

    AbstractPhysicalResource::toJdf(jdfWriter);

    jdfWriter.writeEndElement();
}

MediaLinkSP Media::toLink(ApiHelper::Usage usage) const
{
    MediaLinkSP link = MediaLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

Media::Media()
    : AbstractPhysicalResource(*new MediaPrivate)
{
}

void MediaPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(Media);
    MediaSP castedOther = qSharedPointerCast<Media>(other);
    q->setThickness(castedOther->thickness());
    q->setFrontCoating(castedOther->frontCoating());
    q->setBackCoating(castedOther->backCoating());
    q->setMediaUnit(castedOther->mediaUnit());
    q->setHeight(castedOther->height());
    q->setWidth(castedOther->width());

    AbstractPhysicalResourcePrivate::updateFrom(other);
}
