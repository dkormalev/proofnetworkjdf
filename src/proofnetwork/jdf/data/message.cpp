#include "message.h"

#include "message_p.h"

namespace Proof {
namespace Jdf {

MessageSP instantiateJmfMessage(const QString &tagName, const QString &type)
{
    MessageSP result;
    auto creator = MessagePrivate::messageCreators().value(qMakePair(tagName, type));
    if (creator)
        result = creator();
    return result;
}

QString Message::id() const
{
    Q_D_CONST(Message);
    return d->id;
}

void Message::setId(const QString &arg)
{
    Q_D(Message);
    if (d->id != arg) {
        d->id = arg;
        emit idChanged(d->id);
    }
}

NetworkDataEntityQmlWrapper *Message::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

MessageSP Message::fromJmf(QXmlStreamReader &xmlReader)
{
    MessageSP message;
    if (xmlReader.isStartElement()) {
        QString tag = xmlReader.name().toString();
        auto attributes = xmlReader.attributes();
        QString id = attributes.value(QStringLiteral("ID")).toString();
        QString type = attributes.value(QStringLiteral("Type")).toString();
        message = instantiateJmfMessage(tag, type);
        if (message != nullptr) {
            message->setId(id);
            message->d_func()->specificMessageFromJmf(xmlReader);
        }
    }
    return message;
}

void Message::toJmf(QXmlStreamWriter &xmlWriter)
{
    Q_D(Message);
    xmlWriter.writeStartElement(d->tagName());
    xmlWriter.writeAttribute(QStringLiteral("ID"), d->id);
    xmlWriter.writeAttribute(QStringLiteral("Type"), d->typeName());
    d->specificMessageToJmf(xmlWriter);
    xmlWriter.writeEndElement();
}

Message::Message(MessagePrivate &dd) : NetworkDataEntity(dd)
{}

void Message::updateSelf(const NetworkDataEntitySP &other)
{
    MessageSP castedOther = qSharedPointerCast<Message>(other);
    setId(castedOther->id());
    NetworkDataEntity::updateSelf(other);
}

QHash<MessagePrivate::CreatorKey, MessagePrivate::CreatorType> &MessagePrivate::messageCreators()
{
    static QHash<MessagePrivate::CreatorKey, MessagePrivate::CreatorType> creators;
    return creators;
}

} // namespace Jdf
} // namespace Proof
