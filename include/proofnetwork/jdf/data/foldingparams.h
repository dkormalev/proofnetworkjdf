#ifndef FOLDINGPARAMS_H
#define FOLDINGPARAMS_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamsqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class FoldingParamsPrivate;
class PROOF_NETWORK_JDF_EXPORT FoldingParams : public AbstractResource // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingParams)
public:
    QString foldCatalog() const;
    void setFoldCatalog(const QString &foldCatalog);

    FoldingParamsQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static FoldingParamsSP create();

    static FoldingParamsSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter) override;
    FoldingParamsLinkSP toLink(LinkUsage usage = LinkUsage::InputLink) const;

signals:
    void foldCatalogChanged(const QString &arg);

protected:
    explicit FoldingParams();
};

} // namespace Jdf
} // namespace Proof

#endif // FOLDINGPARAMS_H
