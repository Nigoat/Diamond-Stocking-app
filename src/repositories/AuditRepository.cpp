#include "AuditRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

QList<AuditLog> AuditRepository::getByDiamondId(qint64 diamondId) {
    QList<AuditLog> list;
    if (!DatabaseManager::instance().isOpen()) return list;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "SELECT id, diamond_id, action, field_name, old_value, new_value, timestamp "
        "FROM audit_log WHERE diamond_id = :diamond_id ORDER BY timestamp DESC"
    ));
    q.bindValue(QStringLiteral(":diamond_id"), diamondId);

    if (q.exec()) {
        while (q.next()) {
            AuditLog log;
            log.setId(q.value(0).toLongLong());
            log.setDiamondId(q.value(1).toLongLong());
            log.setAction(q.value(2).toString());
            log.setFieldName(q.value(3).toString());
            log.setOldValue(q.value(4).toString());
            log.setNewValue(q.value(5).toString());
            log.setTimestamp(q.value(6).toString());
            list.append(log);
        }
    }
    return list;
}

bool AuditRepository::logAction(qint64 diamondId, const QString &action, const QString &fieldName,
                                const QString &oldValue, const QString &newValue) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO audit_log (diamond_id, action, field_name, old_value, new_value, timestamp) "
        "VALUES (:diamond_id, :action, :field_name, :old_value, :new_value, datetime('now', 'utc'))"
    ));
    q.bindValue(QStringLiteral(":diamond_id"), diamondId);
    q.bindValue(QStringLiteral(":action"), action);
    q.bindValue(QStringLiteral(":field_name"), fieldName);
    q.bindValue(QStringLiteral(":old_value"), oldValue);
    q.bindValue(QStringLiteral(":new_value"), newValue);

    return q.exec();
}
