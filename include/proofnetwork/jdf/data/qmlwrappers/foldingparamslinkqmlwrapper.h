#ifndef FOLDINGPARAMSLINKQMLWRAPPER_H
#define FOLDINGPARAMSLINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class FoldingParamsLinkQmlWrapperPrivate;
class FoldingParamsLinkQmlWrapper : public AbstractResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FoldingParamsLinkQmlWrapper)
public:
    explicit FoldingParamsLinkQmlWrapper(const FoldingParamsLinkSP &folding, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(FoldingParamsLink)
};

} // namespace Jdf
} // namespace Proof
#endif // FOLDINGPARAMSLINKQMLWRAPPER_H
