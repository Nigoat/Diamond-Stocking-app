#ifndef AUDITREPOSITORY_H
#define AUDITREPOSITORY_H

#include "AuditLog.h"
#include <QList>

class AuditRepository {
public:
    AuditRepository() = default;

    QList<AuditLog> getByDiamondId(qint64 diamondId);
    bool logAction(qint64 diamondId, const QString &action, const QString &fieldName = QString(),
                   const QString &oldValue = QString(), const QString &newValue = QString());
};

#endif
