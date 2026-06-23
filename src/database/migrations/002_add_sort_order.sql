-- Add sort_order column to packs table for ordering behavior and resource packs
-- Version: 2
ALTER TABLE packs ADD COLUMN sort_order INTEGER DEFAULT 0;
