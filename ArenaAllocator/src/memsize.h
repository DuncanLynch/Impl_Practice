#pragma once

class MemSize {
private:
    int size_;

public:
    explicit MemSize(int size) : size_{size} {}

    int getSize() const { return size_; }

    virtual int getSizeInBytes() const = 0;
    virtual ~MemSize() = default;
};

class KiB : public MemSize {
public:
    explicit KiB(int size) : MemSize(size) {}

    int getSizeInBytes() const override {
        return getSize() * 1024;
    }
};

class MiB : public MemSize {
public:
    explicit MiB(int size) : MemSize(size) {}

    int getSizeInBytes() const override {
        return getSize() * 1024 * 1024;
    }
};

class GiB : public MemSize {
public:
    explicit GiB(int size) : MemSize(size) {}

    int getSizeInBytes() const override {
        return getSize() * 1024 * 1024 * 1024;
    }
};
