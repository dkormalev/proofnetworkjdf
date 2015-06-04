#ifndef FOLDINGPARAMS_H
#define FOLDINGPARAMS_H

#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/qmlwrappers/foldingparamsqmlwrapper.h"
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class FoldingParamsPrivate;
class PROOF_NETWORK_JDF_EXPORT FoldingParams : public AbstractResource
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingParams)
public:
    QString foldCatalog() const;
    // TODO: verify foldCatalog
    void setFoldCatalog(const QString &foldCatalog);

    FoldingParamsQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static FoldingParamsSP create();

    static FoldingParamsSP fromJdf(QXmlStreamReader &xmlReader);
    void toJdf(QXmlStreamWriter &jdfWriter);
    static FoldingParamsSP defaultObject();

signals:
    void foldCatalogChanged(const QString &arg);

protected:
    explicit FoldingParams();

};


}
}

#endif // FOLDINGPARAMS_H