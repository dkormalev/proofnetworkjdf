#include "abstractphysicalresource.h"

#include "proofnetwork/jdf/data/abstractphysicalresource_p.h"

using namespace Proof::Jdf;

double AbstractPhysicalResource::amount() const
{
    Q_D(const AbstractPhysicalResource);
    return d->amount;
}

double AbstractPhysicalResource::resourceWeight() const
{
    Q_D(const AbstractPhysicalResource);
    return d->resourceWeight;
}

void AbstractPhysicalResource::setAmount(double arg)
{
    Q_D(AbstractPhysicalResource);
    if (!qFuzzyCompare(d->amount, arg)) {
        d->amount = arg;
        emit amountChanged(d->amount);
    }
}

void AbstractPhysicalResource::setResourceWeight(double arg)
{
    Q_D(AbstractPhysicalResource);
    if (!qFuzzyCompare(d->resourceWeight, arg)) {
        d->resourceWeight = arg;
        emit resourceWeightChanged(d->resourceWeight);
    }
}

bool AbstractPhysicalResource::fromJdf(const QXmlStreamReader &xmlReader,
                                       AbstractPhysicalResourceSP &abstractPhysicalResource)
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    abstractPhysicalResource->setAmount(attributes.value(QStringLiteral("Amount")).toDouble());
    abstractPhysicalResource->setResourceWeight(attributes.value(QStringLiteral("ResourceWeight")).toDouble());

    AbstractResourceSP castedAbstractPhysicalResource = qSharedPointerCast<AbstractResource>(abstractPhysicalResource);
    return AbstractResource::fromJdf(xmlReader, castedAbstractPhysicalResource);
}

void AbstractPhysicalResource::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(AbstractPhysicalResource);
    if (!qFuzzyIsNull(d->amount))
        jdfWriter.writeAttribute(QStringLiteral("Amount"), QString::number(d->amount, 'f', 4));
    if (!qFuzzyIsNull(d->resourceWeight))
        jdfWriter.writeAttribute(QStringLiteral("ResourceWeight"), QString::number(d->resourceWeight, 'f', 4));

    AbstractResource::toJdf(jdfWriter);
}

AbstractPhysicalResource::AbstractPhysicalResource(AbstractPhysicalResourcePrivate &dd, QObject *parent)
    : AbstractResource(dd, parent)
{}

void AbstractPhysicalResourcePrivate::updateFrom(const Proof::NetworkDataEntitySP &other)
{
    Q_Q(AbstractPhysicalResource);
    AbstractPhysicalResourceSP castedOther = qSharedPointerCast<AbstractPhysicalResource>(other);
    q->setAmount(castedOther->amount());
    q->setResourceWeight(castedOther->resourceWeight());

    AbstractResourcePrivate::updateFrom(other);
}
