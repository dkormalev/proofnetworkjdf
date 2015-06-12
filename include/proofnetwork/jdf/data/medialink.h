#ifndef MEDIALINK_H
#define MEDIALINK_H

#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/abstractresourcelink.h"
#include "proofnetwork/jdf/data/media.h"
#include "proofnetwork/jdf/data/qmlwrappers/medialinkqmlwrapper.h"

namespace Proof {
namespace Jdf {

class MediaLinkPrivate;
class MediaLink : public AbstractResourceLink
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MediaLink)
public:
    MediaLinkQmlWrapper *toQmlWrapper(QObject *parent = 0) const override;

    static MediaLinkSP create();

    static MediaLinkSP fromJdf(const QXmlStreamReader &xmlReader);
    virtual void toJdf(QXmlStreamWriter &jdfWriter);

protected:
    explicit MediaLink(QObject *parent = 0);
};

}
}

#endif // MEDIALINK_H