import QtQuick

pragma Singleton

QtObject {
    id: theme

    readonly property bool isDark: Settings ? Settings.theme === "Dark" : true

    readonly property color bgPrimary: isDark ? "#0f172a" : "#f8fafc"
    readonly property color bgSecondary: isDark ? "#1e293b" : "#ffffff"
    readonly property color bgCard: isDark ? "#1e293b" : "#ffffff"
    readonly property color bgInput: isDark ? "#0f172a" : "#f1f5f9"
    readonly property color bgHover: isDark ? "#334155" : "#f1f5f9"
    readonly property color bgSelected: isDark ? "#1e1b4b" : "#e0e7ff"

    readonly property color textPrimary: isDark ? "#f8fafc" : "#0f172a"
    readonly property color textSecondary: isDark ? "#94a3b8" : "#64748b"
    readonly property color textMuted: isDark ? "#64748b" : "#94a3b8"

    readonly property color border: isDark ? "#334155" : "#e2e8f0"
    readonly property color borderFocus: isDark ? "#6366f1" : "#4f46e5"

    readonly property color accent: "#6366f1"
    readonly property color accentHover: "#4f46e5"
    readonly property color accentLight: isDark ? "#312e81" : "#e0e7ff"
    readonly property color accentText: "#ffffff"

    readonly property color success: "#10b981"
    readonly property color successBg: isDark ? "#064e3b" : "#d1fae5"
    readonly property color successText: isDark ? "#6ee7b7" : "#065f46"

    readonly property color warning: "#f59e0b"
    readonly property color warningBg: isDark ? "#78350f" : "#fef3c7"
    readonly property color warningText: isDark ? "#fcd34d" : "#92400e"

    readonly property color danger: "#ef4444"
    readonly property color dangerBg: isDark ? "#7f1d1d" : "#fee2e2"
    readonly property color dangerText: isDark ? "#fca5a5" : "#991b1b"

    readonly property color info: "#0ea5e9"
    readonly property color infoBg: isDark ? "#0c4a6e" : "#e0f2fe"
    readonly property color infoText: isDark ? "#7dd3fc" : "#075985"

    readonly property int radiusSmall: 4
    readonly property int radiusMedium: 8
    readonly property int radiusLarge: 12
    readonly property int radiusFull: 9999

    readonly property int fontSmall: 11
    readonly property int fontNormal: 13
    readonly property int fontMedium: 14
    readonly property int fontLarge: 16
    readonly property int fontHeading: 18
    readonly property int fontTitle: 22

    function statusColor(status) {
        switch (status) {
        case "Available": return theme.success;
        case "Reserved": return theme.warning;
        case "Sold": return theme.info;
        case "Unavailable": return theme.danger;
        case "Returned": return "#a855f7";
        case "Archived": return theme.textMuted;
        default: return theme.textSecondary;
        }
    }

    function statusBgColor(status) {
        switch (status) {
        case "Available": return theme.successBg;
        case "Reserved": return theme.warningBg;
        case "Sold": return theme.infoBg;
        case "Unavailable": return theme.dangerBg;
        case "Returned": return isDark ? "#581c87" : "#f3e8ff";
        case "Archived": return isDark ? "#1e293b" : "#e2e8f0";
        default: return theme.bgInput;
        }
    }

    function statusTextColor(status) {
        switch (status) {
        case "Available": return theme.successText;
        case "Reserved": return theme.warningText;
        case "Sold": return theme.infoText;
        case "Unavailable": return theme.dangerText;
        case "Returned": return isDark ? "#d8b4fe" : "#6b21a8";
        case "Archived": return theme.textMuted;
        default: return theme.textPrimary;
        }
    }
}
