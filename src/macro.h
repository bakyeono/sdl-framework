#ifndef TEMPLATE_MACRO_H
#define TEMPLATE_MACRO_H

#define MACRO_ACCESS(type, name) \
  const type& ##name() { \
    return ##name_; \
  } \
  void set_##name(const ##type& ##name) { \
    ##name_ = name; \
  } \

#define MACRO_ACCESS_VIRTUAL(type, name) \
  virtual const type& ##name() { \
    return ##name_; \
  } \
  virtual void set_##name(const ##type& ##name) { \
    ##name_ = name; \
  } \

#endif // TEMPLATE_MACRO_H
