#include "abstractresource.h"

#include "proofnetwork/jdf/data/abstractresource_p.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"

using namespace Proof::Jdf;

QString AbstractResource::id() const
{
    Q_D(const AbstractResource);
    return d->id;
}

ApiHelper::ResourceStatus AbstractResource::resourceStatus() const
{
    Q_D(const AbstractResource);
    return d->resourceStatus;
}

ApiHelper::ResourceClass AbstractResource::resourceClass() const
{
    Q_D(const AbstractResource);
    return d->resourceClass;
}

QList<ApiHelper::ResourcePartType> AbstractResource::partIdKeys() const
{
    Q_D(const AbstractResource);
    return d->partIdKeys;
}

void AbstractResource::setId(const QString &arg)
{
    Q_D(AbstractResource);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

void AbstractResource::setResourceStatus(ApiHelper::ResourceStatus arg)
{
    Q_D(AbstractResource);
    if (d->resourceStatus != arg) {
        d->resourceStatus = arg;
        emit statusChanged(d->resourceStatus);
    }
}

void AbstractResource::setResourceClass(ApiHelper::ResourceClass arg)
{
    Q_D(AbstractResource);
    if (d->resourceClass != arg) {
        d->resourceClass = arg;
        emit resourceClassChanged(d->resourceClass);
    }
}

void AbstractResource::setPartIdKeys(const QList<ApiHelper::ResourcePartType> &arg)
{
    Q_D(AbstractResource);
    if (d->partIdKeys != arg) {
        d->partIdKeys = arg;
        emit partIdKeysChanged(d->partIdKeys);
    }
}

QString AbstractResource::partAttribute(ApiHelper::ResourcePartType attribute) const
{
    Q_D(const AbstractResource);
    return d->partAttributes.value(attribute, QString());
}

bool AbstractResource::hasPartAttribute(ApiHelper::ResourcePartType attribute) const
{
    Q_D(const AbstractResource);
    return d->partAttributes.contains(attribute);
}

void AbstractResource::setPartAttribute(ApiHelper::ResourcePartType attribute, const QString &value)
{
    Q_D(AbstractResource);
    d->partAttributes[attribute] = value;
    emit partAttributeChanged(attribute, value);
}

bool AbstractResource::fromJdf(const QXmlStreamReader &xmlReader, AbstractResourceSP &abstractResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    QStringList partIdKeysStringified = attributes.value("PartIDKeys").toString().split(" ", QString::SkipEmptyParts);
    QList<ApiHelper::ResourcePartType> partIdKeys;
    for (const QString &partName : partIdKeysStringified) {
        bool ok = false;
        ApiHelper::ResourcePartType part = ApiHelper::resourcePartTypeFromString(partName, &ok);
        if (!ok)
            return false;
        partIdKeys << part;
    }
    abstractResource->setPartIdKeys(partIdKeys);
    abstractResource->setId(attributes.value("ID").toString());
    abstractResource->setResourceStatus(ApiHelper::resourceStatusFromString(attributes.value("Status").toString()));

    for (const auto &attribute : attributes) {
        bool isPartAttribute = false;
        auto part = ApiHelper::resourcePartTypeFromString(attribute.name().toString(), &isPartAttribute);
        if (!isPartAttribute)
            continue;
        abstractResource->setPartAttribute(part, attribute.value().toString());
    }

    return true;
}

void AbstractResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractResource);
    if (!d->id.isEmpty())
        jdfWriter.writeAttribute("ID", d->id);
    if (d->resourceStatus != ApiHelper::ResourceStatus::NoStatus)
        jdfWriter.writeAttribute("Status", ApiHelper::resourceStatusToString(d->resourceStatus));
    if (d->resourceClass != ApiHelper::ResourceClass::NoClass)
        jdfWriter.writeAttribute("Class", ApiHelper::resourceClassToString(d->resourceClass));
    QStringList partIdKeysStringified;
    for (auto part : d->partIdKeys)
        partIdKeysStringified += ApiHelper::resourcePartTypeToString(part);
    if (partIdKeysStringified.count())
        jdfWriter.writeAttribute("PartIDKeys", partIdKeysStringified.join(" "));
    for (auto part : d->partAttributes.keys())
        jdfWriter.writeAttribute(ApiHelper::resourcePartTypeToString(part), d->partAttributes[part]);
}

AbstractResource::AbstractResource(AbstractResourcePrivate &dd, QObject *parent)
    : NetworkDataEntity(dd, parent)
{

}

void AbstractResource::setupLink(const AbstractResourceLinkSP &abstractLink, ApiHelper::Usage usage) const
{
    abstractLink->setRRef(id());
    abstractLink->setUsage(usage);
}

void AbstractResourcePrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AbstractResource);
    AbstractResourceSP castedOther = qSharedPointerCast<AbstractResource>(other);
    q->setId(castedOther->id());
    q->setResourceStatus(castedOther->resourceStatus());
    q->setResourceClass(castedOther->resourceClass());
    q->setPartIdKeys(castedOther->partIdKeys());

    NetworkDataEntityPrivate::updateFrom(other);
}
