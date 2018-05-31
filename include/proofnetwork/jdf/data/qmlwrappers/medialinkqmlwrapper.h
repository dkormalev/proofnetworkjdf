#ifndef MEDIALINKQMLWRAPPER_H
#define MEDIALINKQMLWRAPPER_H

#include "proofnetwork/jdf/data/qmlwrappers/abstractphysicalresourcelinkqmlwrapper.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

namespace Proof {
namespace Jdf {

class MediaLinkQmlWrapperPrivate;
class PROOF_NETWORK_JDF_EXPORT MediaLinkQmlWrapper : public AbstractPhysicalResourceLinkQmlWrapper
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MediaLinkQmlWrapper)
public:
    explicit MediaLinkQmlWrapper(const MediaLinkSP &media, QObject *parent = nullptr);
    PROOF_NDE_WRAPPER_TOOLS(MediaLink)
};

} // namespace Jdf
} // namespace Proof
#endif // MEDIALINKQMLWRAPPER_H
