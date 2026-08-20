#include "AuditLog.h"

AuditLog::AuditLog()
    : m_id(0)
    , m_diamondId(0)
{
}

QVariantMap AuditLog::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("id")] = m_id;
    map[QStringLiteral("diamondId")] = m_diamondId;
    map[QStringLiteral("action")] = m_action;
    map[QStringLiteral("fieldName")] = m_fieldName;
    map[QStringLiteral("oldValue")] = m_oldValue;
    map[QStringLiteral("newValue")] = m_newValue;
    map[QStringLiteral("timestamp")] = m_timestamp;
    return map;
}

AuditLog AuditLog::fromVariantMap(const QVariantMap &map) {
    AuditLog log;
    log.setId(map.value(QStringLiteral("id"), 0).toLongLong());
    log.setDiamondId(map.value(QStringLiteral("diamondId"), 0).toLongLong());
    log.setAction(map.value(QStringLiteral("action")).toString());
    log.setFieldName(map.value(QStringLiteral("fieldName")).toString());
    log.setOldValue(map.value(QStringLiteral("oldValue")).toString());
    log.setNewValue(map.value(QStringLiteral("newValue")).toString());
    log.setTimestamp(map.value(QStringLiteral("timestamp")).toString());
    return log;
}
