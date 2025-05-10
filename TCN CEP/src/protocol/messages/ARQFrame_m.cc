//
// Generated file, do not edit! Created by opp_msgtool 6.1 from protocol/messages/ARQFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "ARQFrame_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(ARQFrame)

ARQFrame::ARQFrame(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

ARQFrame::ARQFrame(const ARQFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

ARQFrame::~ARQFrame()
{
}

ARQFrame& ARQFrame::operator=(const ARQFrame& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ARQFrame::copy(const ARQFrame& other)
{
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
    this->seqNum = other.seqNum;
    this->isAck_ = other.isAck_;
    this->isNak_ = other.isNak_;
    this->lastPacket = other.lastPacket;
    for (size_t i = 0; i < 1000; i++) {
        this->payload[i] = other.payload[i];
    }
}

void ARQFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->seqNum);
    doParsimPacking(b,this->isAck_);
    doParsimPacking(b,this->isNak_);
    doParsimPacking(b,this->lastPacket);
    doParsimArrayPacking(b,this->payload,1000);
}

void ARQFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->seqNum);
    doParsimUnpacking(b,this->isAck_);
    doParsimUnpacking(b,this->isNak_);
    doParsimUnpacking(b,this->lastPacket);
    doParsimArrayUnpacking(b,this->payload,1000);
}

int ARQFrame::getSrcAddress() const
{
    return this->srcAddress;
}

void ARQFrame::setSrcAddress(int srcAddress)
{
    this->srcAddress = srcAddress;
}

int ARQFrame::getDestAddress() const
{
    return this->destAddress;
}

void ARQFrame::setDestAddress(int destAddress)
{
    this->destAddress = destAddress;
}

int ARQFrame::getSeqNum() const
{
    return this->seqNum;
}

void ARQFrame::setSeqNum(int seqNum)
{
    this->seqNum = seqNum;
}

bool ARQFrame::isAck() const
{
    return this->isAck_;
}

void ARQFrame::setIsAck(bool isAck)
{
    this->isAck_ = isAck;
}

bool ARQFrame::isNak() const
{
    return this->isNak_;
}

void ARQFrame::setIsNak(bool isNak)
{
    this->isNak_ = isNak;
}

bool ARQFrame::getLastPacket() const
{
    return this->lastPacket;
}

void ARQFrame::setLastPacket(bool lastPacket)
{
    this->lastPacket = lastPacket;
}

size_t ARQFrame::getPayloadArraySize() const
{
    return 1000;
}

char ARQFrame::getPayload(size_t k) const
{
    if (k >= 1000) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)1000, (unsigned long)k);
    return this->payload[k];
}

void ARQFrame::setPayload(size_t k, char payload)
{
    if (k >= 1000) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)1000, (unsigned long)k);
    this->payload[k] = payload;
}

class ARQFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
        FIELD_destAddress,
        FIELD_seqNum,
        FIELD_isAck,
        FIELD_isNak,
        FIELD_lastPacket,
        FIELD_payload,
    };
  public:
    ARQFrameDescriptor();
    virtual ~ARQFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ARQFrameDescriptor)

ARQFrameDescriptor::ARQFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ARQFrame)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

ARQFrameDescriptor::~ARQFrameDescriptor()
{
    delete[] propertyNames;
}

bool ARQFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ARQFrame *>(obj)!=nullptr;
}

const char **ARQFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ARQFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ARQFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int ARQFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_destAddress
        FD_ISEDITABLE,    // FIELD_seqNum
        FD_ISEDITABLE,    // FIELD_isAck
        FD_ISEDITABLE,    // FIELD_isNak
        FD_ISEDITABLE,    // FIELD_lastPacket
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_payload
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *ARQFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "destAddress",
        "seqNum",
        "isAck",
        "isNak",
        "lastPacket",
        "payload",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int ARQFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "seqNum") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "isAck") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "isNak") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "lastPacket") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *ARQFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_srcAddress
        "int",    // FIELD_destAddress
        "int",    // FIELD_seqNum
        "bool",    // FIELD_isAck
        "bool",    // FIELD_isNak
        "bool",    // FIELD_lastPacket
        "char",    // FIELD_payload
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **ARQFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ARQFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ARQFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        case FIELD_payload: return 1000;
        default: return 0;
    }
}

void ARQFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ARQFrame'", field);
    }
}

const char *ARQFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ARQFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return long2string(pp->getSrcAddress());
        case FIELD_destAddress: return long2string(pp->getDestAddress());
        case FIELD_seqNum: return long2string(pp->getSeqNum());
        case FIELD_isAck: return bool2string(pp->isAck());
        case FIELD_isNak: return bool2string(pp->isNak());
        case FIELD_lastPacket: return bool2string(pp->getLastPacket());
        case FIELD_payload: return long2string(pp->getPayload(i));
        default: return "";
    }
}

void ARQFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: pp->setSrcAddress(string2long(value)); break;
        case FIELD_destAddress: pp->setDestAddress(string2long(value)); break;
        case FIELD_seqNum: pp->setSeqNum(string2long(value)); break;
        case FIELD_isAck: pp->setIsAck(string2bool(value)); break;
        case FIELD_isNak: pp->setIsNak(string2bool(value)); break;
        case FIELD_lastPacket: pp->setLastPacket(string2bool(value)); break;
        case FIELD_payload: pp->setPayload(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ARQFrame'", field);
    }
}

omnetpp::cValue ARQFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress();
        case FIELD_destAddress: return pp->getDestAddress();
        case FIELD_seqNum: return pp->getSeqNum();
        case FIELD_isAck: return pp->isAck();
        case FIELD_isNak: return pp->isNak();
        case FIELD_lastPacket: return pp->getLastPacket();
        case FIELD_payload: return pp->getPayload(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ARQFrame' as cValue -- field index out of range?", field);
    }
}

void ARQFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: pp->setSrcAddress(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destAddress: pp->setDestAddress(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_seqNum: pp->setSeqNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isAck: pp->setIsAck(value.boolValue()); break;
        case FIELD_isNak: pp->setIsNak(value.boolValue()); break;
        case FIELD_lastPacket: pp->setLastPacket(value.boolValue()); break;
        case FIELD_payload: pp->setPayload(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ARQFrame'", field);
    }
}

const char *ARQFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ARQFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ARQFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ARQFrame *pp = omnetpp::fromAnyPtr<ARQFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ARQFrame'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

