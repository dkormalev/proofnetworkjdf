#include "bundleqmlwrapper.h"

#include "proofnetwork/jdf/data/bundle.h"
#include "proofnetwork/jdf/data/bundleitem.h"
#include "proofnetwork/jdf/data/qmlwrappers/bundleitemqmlwrapper.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Jdf {

class BundleQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(BundleQmlWrapper)

    void updateBundleItems();

    QVector<BundleItemQmlWrapper *> bundleItems;
    QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper> qmlBundleItemsList;
    static BundleItemQmlWrapper *bundleItemAt(QQmlListProperty<BundleItemQmlWrapper> *property, int index);
    static int bundleItemsCount(QQmlListProperty<BundleItemQmlWrapper> *property);
};

BundleQmlWrapper::BundleQmlWrapper(const BundleSP &bundle, QObject *parent)
    : NetworkDataEntityQmlWrapper(bundle, *new BundleQmlWrapperPrivate, parent)
{
    setupEntity();
}

BundleQmlWrapper::~BundleQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Bundle)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, Proof::Jdf::BundleType, bundleType)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Bundle, int, totalAmount)

QQmlListProperty<BundleItemQmlWrapper> BundleQmlWrapper::bundleItems() const
{
    Q_D_CONST(BundleQmlWrapper);
    return d->qmlBundleItemsList;
}

void BundleQmlWrapperPrivate::updateBundleItems()
{
    Q_Q(BundleQmlWrapper);
    for (BundleItemQmlWrapper *wrapper : qAsConst(bundleItems))
        wrapper->deleteLater();

    bundleItems.clear();

    BundleSP bundle = q->entity<Bundle>();
    const auto allNdeItems = bundle->bundleItems();
    for (const auto &bundleItem : allNdeItems)
        bundleItems << bundleItem->toQmlWrapper(q);

    qmlBundleItemsList = QQmlListProperty<Proof::Jdf::BundleItemQmlWrapper>(q, &bundleItems,
                                                                            &BundleQmlWrapperPrivate::bundleItemsCount,
                                                                            &BundleQmlWrapperPrivate::bundleItemAt);
    emit q->bundleItemsChanged(qmlBundleItemsList);
}

void BundleQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    Q_D(BundleQmlWrapper);
    BundleSP bundle = entity<Bundle>();
    Q_ASSERT(bundle);

    connect(bundle.data(), &Bundle::bundleTypeChanged, this, &BundleQmlWrapper::bundleTypeChanged);
    connect(bundle.data(), &Bundle::totalAmountChanged, this, &BundleQmlWrapper::totalAmountChanged);
    connect(bundle.data(), &Bundle::bundleItemsChanged, entityConnectContext(), [d]() { d->updateBundleItems(); });

    BundleSP oldBundle = qSharedPointerCast<Bundle>(old);
    if (oldBundle) {
        if (bundle->bundleType() != oldBundle->bundleType())
            emit bundleTypeChanged(bundle->bundleType());
        if (bundle->totalAmount() != oldBundle->totalAmount())
            emit totalAmountChanged(bundle->totalAmount());
    }

    d->updateBundleItems();
}

BundleItemQmlWrapper *BundleQmlWrapperPrivate::bundleItemAt(QQmlListProperty<BundleItemQmlWrapper> *property, int index)
{
    return static_cast<QVector<BundleItemQmlWrapper *> *>(property->data)->at(index);
}

int BundleQmlWrapperPrivate::bundleItemsCount(QQmlListProperty<BundleItemQmlWrapper> *property)
{
    return static_cast<QVector<BundleItemQmlWrapper *> *>(property->data)->count();
}

} // namespace Jdf
} // namespace Proof
