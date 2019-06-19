/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Collections;
import java.util.BitSet;
import java.util.Arrays;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.facebook.thrift.*;
import com.facebook.thrift.async.*;
import com.facebook.thrift.meta_data.*;
import com.facebook.thrift.server.*;
import com.facebook.thrift.transport.*;
import com.facebook.thrift.protocol.*;

@SuppressWarnings({ "unused", "serial" })
public class Val implements TBase, java.io.Serializable, Cloneable, Comparable<Val> {
  private static final TStruct STRUCT_DESC = new TStruct("Val");
  private static final TField STR_VAL_FIELD_DESC = new TField("strVal", TType.STRING, (short)1);
  private static final TField INT_VAL_FIELD_DESC = new TField("intVal", TType.I32, (short)2);
  private static final TField TYPEDEF_VALUE_FIELD_DESC = new TField("typedefValue", TType.MAP, (short)9);

  public String strVal;
  public int intVal;
  public Map<Short,String> typedefValue;
  public static final int STRVAL = 1;
  public static final int INTVAL = 2;
  public static final int TYPEDEFVALUE = 9;
  public static boolean DEFAULT_PRETTY_PRINT = true;

  // isset id assignments
  private static final int __INTVAL_ISSET_ID = 0;
  private BitSet __isset_bit_vector = new BitSet(1);

  public static final Map<Integer, FieldMetaData> metaDataMap;
  static {
    Map<Integer, FieldMetaData> tmpMetaDataMap = new HashMap<Integer, FieldMetaData>();
    tmpMetaDataMap.put(STRVAL, new FieldMetaData("strVal", TFieldRequirementType.DEFAULT, 
        new FieldValueMetaData(TType.STRING)));
    tmpMetaDataMap.put(INTVAL, new FieldMetaData("intVal", TFieldRequirementType.DEFAULT, 
        new FieldValueMetaData(TType.I32)));
    tmpMetaDataMap.put(TYPEDEFVALUE, new FieldMetaData("typedefValue", TFieldRequirementType.DEFAULT, 
        new MapMetaData(TType.MAP, 
            new FieldValueMetaData(TType.I16), 
            new FieldValueMetaData(TType.STRING))));
    metaDataMap = Collections.unmodifiableMap(tmpMetaDataMap);
  }

  static {
    FieldMetaData.addStructMetaDataMap(Val.class, metaDataMap);
  }

  public Val() {
  }

  public Val(
    String strVal,
    int intVal,
    Map<Short,String> typedefValue)
  {
    this();
    this.strVal = strVal;
    this.intVal = intVal;
    setIntValIsSet(true);
    this.typedefValue = typedefValue;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public Val(Val other) {
    __isset_bit_vector.clear();
    __isset_bit_vector.or(other.__isset_bit_vector);
    if (other.isSetStrVal()) {
      this.strVal = TBaseHelper.deepCopy(other.strVal);
    }
    this.intVal = TBaseHelper.deepCopy(other.intVal);
    if (other.isSetTypedefValue()) {
      this.typedefValue = TBaseHelper.deepCopy(other.typedefValue);
    }
  }

  public Val deepCopy() {
    return new Val(this);
  }

  @Deprecated
  public Val clone() {
    return new Val(this);
  }

  public String getStrVal() {
    return this.strVal;
  }

  public Val setStrVal(String strVal) {
    this.strVal = strVal;
    return this;
  }

  public void unsetStrVal() {
    this.strVal = null;
  }

  // Returns true if field strVal is set (has been assigned a value) and false otherwise
  public boolean isSetStrVal() {
    return this.strVal != null;
  }

  public void setStrValIsSet(boolean value) {
    if (!value) {
      this.strVal = null;
    }
  }

  public int getIntVal() {
    return this.intVal;
  }

  public Val setIntVal(int intVal) {
    this.intVal = intVal;
    setIntValIsSet(true);
    return this;
  }

  public void unsetIntVal() {
    __isset_bit_vector.clear(__INTVAL_ISSET_ID);
  }

  // Returns true if field intVal is set (has been assigned a value) and false otherwise
  public boolean isSetIntVal() {
    return __isset_bit_vector.get(__INTVAL_ISSET_ID);
  }

  public void setIntValIsSet(boolean value) {
    __isset_bit_vector.set(__INTVAL_ISSET_ID, value);
  }

  public Map<Short,String> getTypedefValue() {
    return this.typedefValue;
  }

  public Val setTypedefValue(Map<Short,String> typedefValue) {
    this.typedefValue = typedefValue;
    return this;
  }

  public void unsetTypedefValue() {
    this.typedefValue = null;
  }

  // Returns true if field typedefValue is set (has been assigned a value) and false otherwise
  public boolean isSetTypedefValue() {
    return this.typedefValue != null;
  }

  public void setTypedefValueIsSet(boolean value) {
    if (!value) {
      this.typedefValue = null;
    }
  }

  @SuppressWarnings("unchecked")
  public void setFieldValue(int fieldID, Object value) {
    switch (fieldID) {
    case STRVAL:
      if (value == null) {
        unsetStrVal();
      } else {
        setStrVal((String)value);
      }
      break;

    case INTVAL:
      if (value == null) {
        unsetIntVal();
      } else {
        setIntVal((Integer)value);
      }
      break;

    case TYPEDEFVALUE:
      if (value == null) {
        unsetTypedefValue();
      } else {
        setTypedefValue((Map<Short,String>)value);
      }
      break;

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  public Object getFieldValue(int fieldID) {
    switch (fieldID) {
    case STRVAL:
      return getStrVal();

    case INTVAL:
      return new Integer(getIntVal());

    case TYPEDEFVALUE:
      return getTypedefValue();

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  // Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise
  public boolean isSet(int fieldID) {
    switch (fieldID) {
    case STRVAL:
      return isSetStrVal();
    case INTVAL:
      return isSetIntVal();
    case TYPEDEFVALUE:
      return isSetTypedefValue();
    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof Val)
      return this.equals((Val)that);
    return false;
  }

  public boolean equals(Val that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_strVal = true && this.isSetStrVal();
    boolean that_present_strVal = true && that.isSetStrVal();
    if (this_present_strVal || that_present_strVal) {
      if (!(this_present_strVal && that_present_strVal))
        return false;
      if (!TBaseHelper.equalsNobinary(this.strVal, that.strVal))
        return false;
    }

    boolean this_present_intVal = true;
    boolean that_present_intVal = true;
    if (this_present_intVal || that_present_intVal) {
      if (!(this_present_intVal && that_present_intVal))
        return false;
      if (!TBaseHelper.equalsNobinary(this.intVal, that.intVal))
        return false;
    }

    boolean this_present_typedefValue = true && this.isSetTypedefValue();
    boolean that_present_typedefValue = true && that.isSetTypedefValue();
    if (this_present_typedefValue || that_present_typedefValue) {
      if (!(this_present_typedefValue && that_present_typedefValue))
        return false;
      if (!TBaseHelper.equalsNobinary(this.typedefValue, that.typedefValue))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  @Override
  public int compareTo(Val other) {
    if (other == null) {
      // See java.lang.Comparable docs
      throw new NullPointerException();
    }

    if (other == this) {
      return 0;
    }
    int lastComparison = 0;

    lastComparison = Boolean.valueOf(isSetStrVal()).compareTo(other.isSetStrVal());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(strVal, other.strVal);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetIntVal()).compareTo(other.isSetIntVal());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(intVal, other.intVal);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetTypedefValue()).compareTo(other.isSetTypedefValue());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(typedefValue, other.typedefValue);
    if (lastComparison != 0) {
      return lastComparison;
    }
    return 0;
  }

  public void read(TProtocol iprot) throws TException {
    TField field;
    iprot.readStructBegin(metaDataMap);
    while (true)
    {
      field = iprot.readFieldBegin();
      if (field.type == TType.STOP) { 
        break;
      }
      switch (field.id)
      {
        case STRVAL:
          if (field.type == TType.STRING) {
            this.strVal = iprot.readString();
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case INTVAL:
          if (field.type == TType.I32) {
            this.intVal = iprot.readI32();
            setIntValIsSet(true);
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case TYPEDEFVALUE:
          if (field.type == TType.MAP) {
            {
              TMap _map21 = iprot.readMapBegin();
              this.typedefValue = new HashMap<Short,String>(Math.max(0, 2*_map21.size));
              for (int _i22 = 0; 
                   (_map21.size < 0) ? iprot.peekMap() : (_i22 < _map21.size); 
                   ++_i22)
              {
                short _key23;
                String _val24;
                _key23 = iprot.readI16();
                _val24 = iprot.readString();
                this.typedefValue.put(_key23, _val24);
              }
              iprot.readMapEnd();
            }
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        default:
          TProtocolUtil.skip(iprot, field.type);
          break;
      }
      iprot.readFieldEnd();
    }
    iprot.readStructEnd();


    // check for required fields of primitive type, which can't be checked in the validate method
    validate();
  }

  public void write(TProtocol oprot) throws TException {
    validate();

    oprot.writeStructBegin(STRUCT_DESC);
    if (this.strVal != null) {
      oprot.writeFieldBegin(STR_VAL_FIELD_DESC);
      oprot.writeString(this.strVal);
      oprot.writeFieldEnd();
    }
    oprot.writeFieldBegin(INT_VAL_FIELD_DESC);
    oprot.writeI32(this.intVal);
    oprot.writeFieldEnd();
    if (this.typedefValue != null) {
      oprot.writeFieldBegin(TYPEDEF_VALUE_FIELD_DESC);
      {
        oprot.writeMapBegin(new TMap(TType.I16, TType.STRING, this.typedefValue.size()));
        for (Map.Entry<Short, String> _iter25 : this.typedefValue.entrySet())        {
          oprot.writeI16(_iter25.getKey());
          oprot.writeString(_iter25.getValue());
        }
        oprot.writeMapEnd();
      }
      oprot.writeFieldEnd();
    }
    oprot.writeFieldStop();
    oprot.writeStructEnd();
  }

  @Override
  public String toString() {
    return toString(DEFAULT_PRETTY_PRINT);
  }

  @Override
  public String toString(boolean prettyPrint) {
    return toString(1, prettyPrint);
  }

  @Override
  public String toString(int indent, boolean prettyPrint) {
    String indentStr = prettyPrint ? TBaseHelper.getIndentedString(indent) : "";
    String newLine = prettyPrint ? "\n" : "";
String space = prettyPrint ? " " : "";
    StringBuilder sb = new StringBuilder("Val");
    sb.append(space);
    sb.append("(");
    sb.append(newLine);
    boolean first = true;

    sb.append(indentStr);
    sb.append("strVal");
    sb.append(space);
    sb.append(":").append(space);
    if (this.getStrVal() == null) {
      sb.append("null");
    } else {
      sb.append(TBaseHelper.toString(this.getStrVal(), indent + 1, prettyPrint));
    }
    first = false;
    if (!first) sb.append("," + newLine);
    sb.append(indentStr);
    sb.append("intVal");
    sb.append(space);
    sb.append(":").append(space);
    sb.append(TBaseHelper.toString(this.getIntVal(), indent + 1, prettyPrint));
    first = false;
    if (!first) sb.append("," + newLine);
    sb.append(indentStr);
    sb.append("typedefValue");
    sb.append(space);
    sb.append(":").append(space);
    if (this.getTypedefValue() == null) {
      sb.append("null");
    } else {
      sb.append(TBaseHelper.toString(this.getTypedefValue(), indent + 1, prettyPrint));
    }
    first = false;
    sb.append(newLine + TBaseHelper.reduceIndent(indentStr));
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws TException {
    // check for required fields
    // check that fields of type enum have valid values
  }

}

