#ifndef FIELD_H
#define FIELD_H

class Character;

class Field {
public:
    virtual void applyEffect(Character& character) = 0;
};

class EmptyField : public Field {
public:
    void applyEffect(Character& character) override;
};

class DangerField : public Field {
public:
    void applyEffect(Character& character) override;
};

class FountainField : public Field {
public:
    void applyEffect(Character& character) override;
};

class RelicField : public Field {
public:
    void applyEffect(Character& character) override;
};

#endif

