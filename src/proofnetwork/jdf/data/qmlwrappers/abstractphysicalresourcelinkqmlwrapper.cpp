#include "abstractphysicalresourcelinkqmlwrapper.h"

#include "proofnetwork/jdf/data/abstractphysicalresourcelink.h"
#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper_p.h"

using namespace Proof::Jdf;

AbstractPhysicalResourceLinkQmlWrapper::AbstractPhysicalResourceLinkQmlWrapper(
    const QSharedPointer<AbstractPhysicalResourceLink> &link, AbstractPhysicalResourceLinkQmlWrapperPrivate &dd,
    QObject *parent)
    : AbstractResourceLinkQmlWrapper(link, dd, parent)
{
    setupEntity();
}

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResourceLink, Proof::Jdf::ResourceOrientation, orientation)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(AbstractPhysicalResourceLink, double, amount)

void AbstractPhysicalResourceLinkQmlWrapper::setupEntity(const QSharedPointer<Proof::NetworkDataEntity> &old)
{
    AbstractPhysicalResourceLinkSP link = entity<AbstractPhysicalResourceLink>();
    Q_ASSERT(link);

    connect(link.data(), &AbstractPhysicalResourceLink::orientationChanged, this,
            &AbstractPhysicalResourceLinkQmlWrapper::orientationChanged);
    connect(link.data(), &AbstractPhysicalResourceLink::amountChanged, this,
            &AbstractPhysicalResourceLinkQmlWrapper::amountChanged);

    AbstractPhysicalResourceLinkSP oldLink = qSharedPointerCast<AbstractPhysicalResourceLink>(old);
    if (oldLink) {
        if (link->orientation() != oldLink->orientation())
            emit orientationChanged(link->orientation());
        if (link->amount() != oldLink->amount())
            emit amountChanged(link->amount());
    }
}
