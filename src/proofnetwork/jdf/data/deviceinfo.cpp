#include "deviceinfo.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class DeviceInfoPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DeviceInfo)

    QString deviceId;
    ApiHelper::DeviceStatus status = ApiHelper::DeviceStatus::UnknownDeviceStatus;
    ApiHelper::DeviceCondition condition = ApiHelper::DeviceCondition::OkDeviceCondition;
};

QString DeviceInfo::deviceId() const
{
    Q_D(const DeviceInfo);
    return d->deviceId;
}

ApiHelper::DeviceStatus Proof::Jdf::DeviceInfo::status() const
{
    Q_D(const DeviceInfo);
    return d->status;
}

ApiHelper::DeviceCondition DeviceInfo::condition() const
{
    Q_D(const DeviceInfo);
    return d->condition;
}

void DeviceInfo::setDeviceId(const QString &arg)
{
    Q_D(DeviceInfo);
    if (d->deviceId != arg) {
        d->deviceId = arg;
        emit deviceIdChanged(d->deviceId);
    }
}

void Proof::Jdf::DeviceInfo::setStatus(ApiHelper::DeviceStatus arg)
{
    Q_D(DeviceInfo);
    if (d->status != arg) {
        d->status = arg;
        emit statusChanged(d->status);
    }
}

void Proof::Jdf::DeviceInfo::setCondition(ApiHelper::DeviceCondition arg)
{
    Q_D(DeviceInfo);
    if (d->condition != arg) {
        d->condition = arg;
        emit conditionChanged(d->condition);
    }
}

NetworkDataEntityQmlWrapper *DeviceInfo::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

DeviceInfoSP DeviceInfo::create()
{
    DeviceInfoSP result(new DeviceInfo());
    initSelfWeakPtr(result);
    return result;
}

DeviceInfoSP DeviceInfo::fromJmf(QXmlStreamReader &xmlReader)
{
    DeviceInfoSP deviceInfo;
    if (xmlReader.isStartElement() && xmlReader.name() == "DeviceInfo") {
        deviceInfo = create();
        deviceInfo->setFetched(true);
        auto attributes = xmlReader.attributes();
        deviceInfo->setDeviceId(attributes.value("DeviceID").toString());
        deviceInfo->setStatus(ApiHelper::deviceStatusFromString(attributes.value("DeviceStatus").toString()));
        deviceInfo->setCondition(ApiHelper::deviceConditionFromString(attributes.value("DeviceCondition").toString()));
    }
    xmlReader.skipCurrentElement();
    return deviceInfo;
}

void DeviceInfo::toJmf(QXmlStreamWriter &xmlWriter)
{
    Q_D(DeviceInfo);
    xmlWriter.writeStartElement("DeviceInfo");
    xmlWriter.writeAttribute("DeviceID", d->deviceId);
    xmlWriter.writeAttribute("DeviceStatus", ApiHelper::deviceStatusToString(d->status));
    xmlWriter.writeAttribute("DeviceCondition", ApiHelper::deviceConditionToString(d->condition));
    xmlWriter.writeEndElement();
}

DeviceInfo::DeviceInfo()
    : NetworkDataEntity(*new DeviceInfoPrivate)
{
}

} // namespace Jdf
} // namespace Proof
