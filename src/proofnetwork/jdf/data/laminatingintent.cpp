#include "laminatingintent.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/laminatingintentlink.h"
#include "proofnetwork/jdf/data/qmlwrappers/laminatingintentqmlwrapper.h"

namespace Proof {
namespace Jdf {

class LaminatingIntentPrivate : AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(LaminatingIntent)

    LaminatingIntentPrivate() : AbstractResourcePrivate(ResourceClass::IntentClass) {}

    LaminatingSurface surface = LaminatingSurface::NoneLaminated;
};

} // namespace Jdf
} // namespace Proof

using namespace Proof::Jdf;

LaminatingSurface LaminatingIntent::surface() const
{
    Q_D_CONST(LaminatingIntent);
    return d->surface;
}

void LaminatingIntent::setSurface(LaminatingSurface surface)
{
    Q_D(LaminatingIntent);
    if (d->surface != surface) {
        d->surface = surface;
        emit surfaceChanged(surface);
    }
}

LaminatingIntentQmlWrapper *LaminatingIntent::toQmlWrapper(QObject *parent) const
{
    LaminatingIntentSP castedSelf = castedSelfPtr<LaminatingIntent>();
    Q_ASSERT(castedSelf);
    return new LaminatingIntentQmlWrapper(castedSelf, parent);
}

LaminatingIntentSP LaminatingIntent::create()
{
    LaminatingIntentSP result(new LaminatingIntent());
    initSelfWeakPtr(result);
    return result;
}

LaminatingIntentSP LaminatingIntent::fromJdf(QXmlStreamReader &xmlReader)
{
    LaminatingIntentSP laminatingIntent = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "LaminatingIntent" && xmlReader.isStartElement() && !laminatingIntent->isFetched()) {
            laminatingIntent->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            laminatingIntent->setSurface(
                laminatingSurfaceFromString(attributes.value(QStringLiteral("Surface")).toString()));
            AbstractResourceSP castedLaminatingIntent = qSharedPointerCast<AbstractResource>(laminatingIntent);
            AbstractResource::fromJdf(xmlReader, castedLaminatingIntent);

        } else if (xmlReader.isStartElement()) {
            xmlReader.skipCurrentElement();
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return laminatingIntent;
}

void LaminatingIntent::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(LaminatingIntent);

    jdfWriter.writeStartElement(QStringLiteral("LaminatingIntent"));
    jdfWriter.writeAttribute(QStringLiteral("Surface"), laminatingSurfaceToString(d->surface));
    AbstractResource::toJdf(jdfWriter);
    jdfWriter.writeEndElement();
}

LaminatingIntentLinkSP LaminatingIntent::toLink(LinkUsage usage) const
{
    LaminatingIntentLinkSP link = LaminatingIntentLink::create();
    AbstractResource::setupLink(link, usage);
    return link;
}

LaminatingIntent::LaminatingIntent() : AbstractResource(*new LaminatingIntentPrivate)
{}

void LaminatingIntent::updateSelf(const Proof::NetworkDataEntitySP &other)
{
    LaminatingIntentSP castedOther = qSharedPointerCast<LaminatingIntent>(other);
    setSurface(castedOther->surface());

    AbstractResource::updateSelf(other);
}
