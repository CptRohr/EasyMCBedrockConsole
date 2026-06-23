-- Initial Database Schema for Bedrock Addon Manager
-- Version: 1

-- Schema version tracking
CREATE TABLE IF NOT EXISTS schema_version (
    version INTEGER PRIMARY KEY,
    applied_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Installed addons/packs registry
CREATE TABLE IF NOT EXISTS packs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    uuid TEXT NOT NULL UNIQUE,
    name TEXT NOT NULL,
    version_major INTEGER NOT NULL,
    version_minor INTEGER NOT NULL,
    version_patch INTEGER NOT NULL,
    pack_type TEXT NOT NULL CHECK(pack_type IN ('behavior', 'resource', 'skin')),
    description TEXT,
    author TEXT,
    install_path TEXT NOT NULL,
    is_enabled INTEGER DEFAULT 1,
    installed_at TEXT DEFAULT CURRENT_TIMESTAMP,
    min_engine_major INTEGER DEFAULT 1,
    min_engine_minor INTEGER DEFAULT 20,
    min_engine_patch INTEGER DEFAULT 0,
    sort_order INTEGER DEFAULT 0
);

-- Pack dependencies
CREATE TABLE IF NOT EXISTS pack_dependencies (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    pack_id INTEGER NOT NULL,
    dep_uuid TEXT NOT NULL,
    dep_version_major INTEGER NOT NULL,
    dep_version_minor INTEGER NOT NULL,
    dep_version_patch INTEGER NOT NULL,
    FOREIGN KEY(pack_id) REFERENCES packs(id) ON DELETE CASCADE
);

-- Discovered worlds
CREATE TABLE IF NOT EXISTS worlds (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    folder_name TEXT NOT NULL UNIQUE,
    display_name TEXT,
    world_path TEXT NOT NULL,
    last_seen TEXT DEFAULT CURRENT_TIMESTAMP
);

-- World-pack assignments (behavior and resource packs per world)
CREATE TABLE IF NOT EXISTS world_pack_assignments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    world_id INTEGER NOT NULL,
    pack_id INTEGER NOT NULL,
    sort_order INTEGER NOT NULL,
    is_enabled INTEGER DEFAULT 1,
    assigned_at TEXT DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(world_id) REFERENCES worlds(id) ON DELETE CASCADE,
    FOREIGN KEY(pack_id) REFERENCES packs(id) ON DELETE CASCADE,
    UNIQUE(world_id, pack_id)
);

-- Validation results log
CREATE TABLE IF NOT EXISTS validation_log (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    run_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    trigger TEXT CHECK(trigger IN ('startup', 'manual', 'install')),
    result_json TEXT,
    passed INTEGER
);

-- Create indexes for common queries
CREATE INDEX IF NOT EXISTS idx_packs_uuid ON packs(uuid);
CREATE INDEX IF NOT EXISTS idx_packs_type ON packs(pack_type);
CREATE INDEX IF NOT EXISTS idx_pack_dependencies_pack_id ON pack_dependencies(pack_id);
CREATE INDEX IF NOT EXISTS idx_worlds_folder ON worlds(folder_name);
CREATE INDEX IF NOT EXISTS idx_world_pack_assignments_world_id ON world_pack_assignments(world_id);
CREATE INDEX IF NOT EXISTS idx_world_pack_assignments_pack_id ON world_pack_assignments(pack_id);
