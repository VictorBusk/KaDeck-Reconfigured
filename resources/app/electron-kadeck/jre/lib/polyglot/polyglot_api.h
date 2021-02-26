#ifndef __POLYGLOT_API_H
#define __POLYGLOT_API_H

#include <stdint.h>
#include <polyglot_isolate.h>
#include <polyglot_types.h>
/*
 * Polyglot Native API is in experimental phase of development and should not be used in production environments.
 *
 * Future versions will introduce modifications to the API in backward incompatible ways. Feel free to use the API
 * for examples and experiments and keep us posted about the features that you need or you feel are awkward.
 */

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Creates a new context builder that allows to configure an engine instance.
 * 
 *  @since 19.0
 */
poly_status poly_create_engine_builder(poly_thread thread, poly_engine_builder* result);

/*
 * Sets an option for an <code>poly_engine_builder</code> that will apply to constructed engines.
 * <p>
 * 
 *  @param engine_builder that is assigned an option.
 *  @param key_utf8 0 terminated and UTF-8 encoded key for the option.
 *  @param value_utf8 0 terminated and UTF-8 encoded value for the option.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_engine_builder_option(poly_thread thread, poly_engine_builder engine_builder, const char* key_utf8, const char* value_utf8);

/*
 * Builds an <code>engine</code> from an <code>engine_builder</code>. The same builder can be used to 
 * produce multiple <code>poly_engine</code> instances.
 * 
 *  @param engine_builder that is used to build.
 *  @param result the created engine.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_engine_builder_build(poly_thread thread, poly_engine_builder engine_builder, poly_engine* result);

/*
 * Creates a polyglot engine: An execution engine for Graal guest languages that allows to inspect the 
 * installed languages and can have multiple execution contexts.
 * 
 * Engine is a unit that holds configuration, instruments, and compiled code for all contexts assigned 
 * to this engine.
 *  @since 19.0
 */
poly_status poly_create_engine(poly_thread thread, poly_engine* result);

/*
 * Closes this engine and frees up allocated native resources. If there are still open context
 * instances that were created using this engine and they are currently not being executed then
 * they will be closed automatically. If an attempt to close an engine was successful then
 * consecutive calls to close have no effect. If a context is cancelled then the currently
 * executing thread will throw a {@link PolyglotException}.
 * 
 *  @param engine to be closed.
 *  @param cancel_if_executing if <code>true</code> then currently executing contexts will be cancelled.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_engine_close(poly_thread thread, poly_engine engine, bool cancel_if_executing);

/*
 * Returns an array of size returned by {@link poly_engine_get_languages_size} where each element is a <code>poly_language<code> handle.
 * 
 *  @param engine for which languages are returned.
 *  @param language_array array to write <code>poly_language</code>s to or NULL.
 *  @param size the number of languages in the engine.
 *  @since 19.0
 */
poly_status poly_engine_get_languages(poly_thread thread, poly_engine engine, poly_language* language_array, size_t* size);

/*
 * Creates a context with a new engine polyglot engine with a list 
 * 
 * A context holds all of the program data. Each context is by default isolated from all other contexts
 * with respect to program data and evaluation semantics.
 * 
 *  @param permittedLanguages array of 0 terminated language identifiers in UTF-8 that are permitted.
 *  @param length of the array of language identifiers.
 *  @param result the created context.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_create_context_builder(poly_thread thread, const char** permitted_languages, size_t length, poly_context_builder* result);

/*
 * Sets an engine for the context builder.
 * 
 *  @param context_builder that is assigned an engine.
 *  @param engine to assign to this builder.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_engine(poly_thread thread, poly_context_builder context_builder, poly_engine engine);

/*
 * Sets an option on a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is assigned an option.
 *  @param key_utf8 0 terminated and UTF-8 encoded key for the option.
 *  @param value_utf8 0 terminated and UTF-8 encoded value for the option.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_option(poly_thread thread, poly_context_builder context_builder, const char* key_utf8, const char* value_utf8);

/*
 * Allows or disallows all access for a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is modified.
 *  @param allow_all_access bool value that defines all access.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_allow_all_access(poly_thread thread, poly_context_builder context_builder, bool allow_all_access);

/*
 * Allows or disallows IO for a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is modified.
 *  @param allow_IO bool value that is passed to the builder.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_allow_io(poly_thread thread, poly_context_builder context_builder, bool allow_IO);

/*
 * Allows or disallows native access for a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is modified.
 *  @param allow_native_access bool value that is passed to the builder.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_allow_native_access(poly_thread thread, poly_context_builder context_builder, bool allow_native_access);

/*
 * Allows or disallows polyglot access for a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is modified.
 *  @param allow_polyglot_access bool value that is passed to the builder.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_allow_polyglot_access(poly_thread thread, poly_context_builder context_builder, bool allow_polyglot_access);

/*
 * Allows or disallows thread creation for a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is modified.
 *  @param allow_create_thread bool value that is passed to the builder.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_allow_create_thread(poly_thread thread, poly_context_builder context_builder, bool allow_create_thread);

/*
 * Allows or disallows experimental options for a <code>poly_context_builder</code>.
 * 
 *  @param context_builder that is modified.
 *  @param allow_experimental_options bool value that is passed to the builder.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_allow_experimental_options(poly_thread thread, poly_context_builder context_builder, bool allow_experimental_options);

/*
 * Builds a <code>context</code> from a <code>context_builder</code>. The same builder can be used to 
 * produce multiple <code>poly_context</code> instances.
 * 
 *  @param context_builder that is used to construct a new context.
 *  @param result the created context.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_builder_build(poly_thread thread, poly_context_builder context_builder, poly_context* result);

/*
 * Creates a context with default configuration.
 * 
 * A context holds all of the program data. Each context is by default isolated from all other contexts
 * with respect to program data and evaluation semantics.
 * 
 *  @param permitted_languages array of 0 terminated language identifiers in UTF-8 that are permitted, or NULL for 
 *         supporting all available languages.
 *  @param length of the array of language identifiers.
 *  @param result the created context.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_create_context(poly_thread thread, const char** permitted_languages, size_t length, poly_context* result);

/*
 * Closes this context and frees up potentially allocated native resources. A 
 * context cannot free all native resources allocated automatically. For this reason
 * it is necessary to close contexts after use. If a context is canceled then the
 * currently executing thread will throw a {@link PolyglotException}. Please note 
 * that canceling a single context can negatively affect the performance of other 
 * executing contexts constructed with the same engine.
 * <p>
 * If internal errors occur during closing of the language then they are printed to the 
 * configured {@link Builder#err(OutputStream) error output stream}. If a context was 
 * closed then all its methods will throw an {@link IllegalStateException} when invoked. 
 * If an attempt to close a context was successful then consecutive calls to close have 
 * no effect.
 * 
 *  @param context to be closed.
 *  @param cancel_if_executing if <code>true</code> then currently executing context will be cancelled.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @since 19.0
 */
poly_status poly_context_close(poly_thread thread, poly_context context, bool cancel_if_executing);

/*
 * Evaluate a source of guest languages inside a context.
 * 
 *  @param context in which we evaluate source code.
 *  @param language_id the language identifier.
 *  @param name_utf8 given to the evaluate source code.
 *  @param source_utf8 the source code to be evaluated.
 *  @param result <code>poly_value</code> that is the result of the evaluation.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @see org::graalvm::polyglot::Context::eval
 *  @since 19.0
 */
poly_status poly_context_eval(poly_thread thread, poly_context context, const char* language_id, const char* name_utf8, const char* source_utf8, poly_value* result);

/*
 * Returns the engine this context belongs to.
 * 
 *  @param context for which we extract the bindings.
 *  @param result a value whose members correspond to the symbols in the top scope of the `language_id`.
 *  @return poly_ok if everything is fine, poly_generic_failure if there is an error.
 *  @see org::graalvm::polyglot::Context::getEngine
 *  @since 19.0
 */
poly_status poly_context_get_engine(poly_thread thread, poly_context context, poly_value* result);

/*
 * Returns a value that represents the top-most bindings of a language. The top-most bindings of
 * the language are a value whose members correspond to each symbol in the top scope.
 * 
 * Languages may allow modifications of members of the returned bindings object at the
 * language's discretion. If the language was not yet initialized it
 * will be initialized when the bindings are requested.
 * 
 *  @param context for which we extract the bindings.
 *  @param language_id the language identifier.
 *  @param result a value whose members correspond to the symbols in the top scope of the `language_id`.
 *  @return poly_generic_failure if the language does not exist, if context is already closed, 
 *         in case the lazy initialization failed due to a guest language error.
 *  @see org::graalvm::polyglot::Context::getBindings
 *  @since 19.0
 */
poly_status poly_context_get_bindings(poly_thread thread, poly_context context, const char* language_id, poly_value* result);

/*
 * Returns polyglot bindings that may be used to exchange symbols between the host and 
 * guest languages. All languages have unrestricted access to the polyglot bindings. 
 * The returned bindings object always has members and its members are readable, writable and removable.
 * 
 * Guest languages may put and get members through language specific APIs. For example, 
 * in JavaScript symbols of the polyglot bindings can be accessed using 
 * `Polyglot.import("name")` and set using `Polyglot.export("name", value)`. Please see 
 * the individual language reference on how to access these symbols.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is already closed.
 *  @see org::graalvm::polyglot::Context::getPolyglotBindings
 *  @since 19.0
 */
poly_status poly_context_get_polyglot_bindings(poly_thread thread, poly_context context, poly_value* result);

/*
 * Checks whether a polyglot value can be executed.
 * 
 *  @param value a polyglot value.
 *  @param result true if the value can be executed, false otherwise.
 *  @return poly_ok if all works, poly_generic_error if there is a failure.
 *  @see org::graalvm::polyglot::Value::canExecute
 *  @since 19.0
 */
poly_status poly_value_can_execute(poly_thread thread, poly_value value, bool* result);

/*
 * Executes a value if it can be executed and returns its result. All arguments passed 
 * must be polyglot values.
 * 
 *  @param value to be executed.
 *  @param args array of poly_value.
 *  @param args_size length of the args array.
 *  @return poly_ok if all works, poly_generic_error if the underlying context was closed, if a wrong 
 *          number of arguments was provided or one of the arguments was not applicable, if this value cannot be executed,
 *  and if a guest language error occurred during execution.
 *  @see org::graalvm::polyglot::Value::execute
 *  @since 19.0
 */
poly_status poly_value_execute(poly_thread thread, poly_value value, poly_value* args, int32_t args_size, poly_value* result);

/*
 * Returns the member with a given `utf8_identifier` or `null` if the member does not exist.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the value has no members, the given identifier exists 
 *         but is not readable, if a guest language error occurred during execution.
 *  @see org::graalvm::polyglot::Value::getMember
 *  @since 19.0
 */
poly_status poly_value_get_member(poly_thread thread, poly_value value, const char* utf8_identifier, poly_value* result);

/*
 * Sets the value of a member with the `utf8_identifier`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the context is already closed, if the value does 
 *          not have any members, the key does not exist and new members cannot be added, or the existing 
 *          member is not modifiable.
 *  @see org::graalvm::polyglot::Value::putMember
 *  @since 19.0
 */
poly_status poly_value_put_member(poly_thread thread, poly_value value, const char* utf8_identifier, poly_value member);

/*
 * Returns `true` if such a member exists for the given `utf8_identifier`. If the value has no members 
 * then it returns `false`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *          during execution.
 *  @see org::graalvm::polyglot::Value::putMember
 *  @since 19.0
 */
poly_status poly_value_has_member(poly_thread thread, poly_value value, const char* utf8_identifier, bool* result);

/*
 * Creates a polyglot boolean value from a C boolean.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_boolean(poly_thread thread, poly_context context, bool value, poly_value* result);

/*
 * Creates a polyglot integer number from `int8_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_int8(poly_thread thread, poly_context context, int8_t value, poly_value* result);

/*
 * Creates a polyglot integer number from `int16_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_int16(poly_thread thread, poly_context context, int16_t value, poly_value* result);

/*
 * Creates a polyglot integer number from `int32_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_int32(poly_thread thread, poly_context context, int32_t value, poly_value* result);

/*
 * Creates a polyglot integer number from `int64_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_int64(poly_thread thread, poly_context context, int64_t value, poly_value* result);

/*
 * Creates a polyglot integer number from `uint8_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_uint8(poly_thread thread, poly_context context, uint8_t value, poly_value* result);

/*
 * Creates a polyglot integer number from `uint16_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_uint16(poly_thread thread, poly_context context, uint16_t value, poly_value* result);

/*
 * Creates a polyglot integer number from `uint32_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_uint32(poly_thread thread, poly_context context, uint32_t value, poly_value* result);

/*
 * Creates a polyglot floating point number from C `float`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_float(poly_thread thread, poly_context context, float value, poly_value* result);

/*
 * Creates a polyglot floating point number from C `double`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_double(poly_thread thread, poly_context context, double value, poly_value* result);

/*
 * Creates a polyglot character from C `char`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_character(poly_thread thread, poly_context context, int16_t character, poly_value* result);

/*
 * Creates a polyglot string from an UTF-8 encoded string. Only the `length` of the string in bytes is used unless
 * `POLY_AUTO_LENGTH` is passed as the `length` argument.
 * 
 *  @param string the C string, null terminated or not.
 *  @param length the length of C string, or POLY_AUTO_LENGTH if the string is null terminated.
 *  @return the polyglot string value.
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_string_utf8(poly_thread thread, poly_context context, const char* string, size_t length, poly_value* result);

/*
 * Creates the polyglot `null` value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::Context::asValue
 *  @since 19.0
 */
poly_status poly_create_null(poly_thread thread, poly_context context, poly_value* result);

/*
 * Creates a polyglot object with no members.
 * 
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed.
 *  @see org::graalvm::polyglot::ProxyObject::fromMap
 *  @since 19.0
 */
poly_status poly_create_object(poly_thread thread, poly_context context, poly_value* result);

/*
 * Creates a polyglot array from the C array of polyglot values.
 * 
 *  @param value_array array containing polyglot values
 *  @param array_length the number of elements in the value_array
 *  @return poly_ok if all works, poly_generic_failure if context is null, if the underlying context was closed, 
 *          if the array does not contain polyglot values.
 *  @see org::graalvm::polyglot::ProxyArray::fromList
 *  @since 19.0
 */
poly_status poly_create_array(poly_thread thread, poly_context context, const poly_value* value_array, int64_t array_length, poly_value* result);

/*
 * Check whether a polyglot value has array elements. 
 * 
 * If yes, array elements can be accessed using {@link poly_value_get_array_element}, 
 * {@link poly_value_set_array_element}, {@link poly_value_remove_array_element} and the array size 
 * can be queried using {@link poly_value_get_array_size}.
 * 
 *  @param value value that we are checking.
 *  @return true if the value has array elements.
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::hasArrayElements
 *  @since 19.0
 */
poly_status poly_value_has_array_elements(poly_thread thread, poly_value value, bool* result);

/*
 * Returns an array element from the specified index. 
 * 
 * Polyglot arrays start with index `0`, independent of the guest language. The given array index must 
 * be greater or equal 0.
 * 
 *  @param value value that has array elements.
 *  @param index index of the element starting from 0.
 *  @return the array element.
 *  @return poly_ok if all works, poly_generic_failure if the array index does not exist, if index is not readable, if the 
 *          underlying context was closed, if guest language error occurred during execution, poly_array_expected if the 
 *          value has no array elements.
 *  @see org::graalvm::polyglot::Value::getArrayElement
 *  @since 19.0
 */
poly_status poly_value_get_array_element(poly_thread thread, poly_value value, int64_t index, poly_value* result);

/*
 * Sets the value at a given index.
 * 
 * Polyglot arrays start with index `0`, independent of the guest language. The given array index must 
 * be greater or equal 0.
 * 
 *  @param value value that we are checking.
 *  @param index index of the element starting from 0.
 *  @param element to be written into the array.
 *  @param result true if the value has array elements.
 *  @return poly_ok if all works, poly_generic_failure if the array index does not exist, if index is not writeable, if the 
 *          underlying context was closed, if guest language error occurred during execution, poly_array_expected if the value has no array elements..
 *  @see org::graalvm::polyglot::Value::setArrayElement
 *  @since 19.0
 */
poly_status poly_value_set_array_element(poly_thread thread, poly_value value, int64_t index, poly_value element);

/*
 * Removes an array element at a given index.
 * 
 * Polyglot arrays start with index `0`, independent of the guest language. The given array index must 
 * be greater or equal 0.
 * 
 *  @param value value that we are checking.
 *  @param index index of the element starting from 0.
 *  @param result true if the underlying array element could be removed, otherwise false.
 *  @return poly_ok if all works, poly_generic_failure if the array index does not exist, if index is not removable, if the 
 *          underlying context was closed, if guest language error occurred during execution, poly_array_expected if the 
 *          value has no array elements.
 *  @see org::graalvm::polyglot::Value::removeArrayElement
 *  @since 19.0
 */
poly_status poly_value_remove_array_element(poly_thread thread, poly_value value, int64_t index, bool* result);

/*
 * Gets the size of the polyglot value that has array elements.
 * 
 *  @param value value that has array elements.
 *  @param result number of elements in the value.
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *          during execution, poly_array_expected if the value has no array elements.
 *  @see org::graalvm::polyglot::Value::removeArrayElement
 *  @since 19.0
 */
poly_status poly_value_get_array_size(poly_thread thread, poly_value value, int64_t* result);

/*
 * Returns `true` if this value is `null` like.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::isNull
 *  @since 19.0
 */
poly_status poly_value_is_null(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value represents a boolean value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *         if the underlying context was closed, if value could not be converted. 
 *  @see org::graalvm::polyglot::Value::isBoolean
 *  @since 19.0
 */
poly_status poly_value_is_boolean(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value represents a string.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::isString
 *  @since 19.0
 */
poly_status poly_value_is_string(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value represents a number.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::isNumber
 *  @since 19.0
 */
poly_status poly_value_is_number(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into a C float.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::fitsInFloat
 *  @since 19.0
 */
poly_status poly_value_fits_in_float(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into a C double.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::fitsInDouble
 *  @since 19.0
 */
poly_status poly_value_fits_in_double(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `int8_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::fitsInByte
 *  @since 19.0
 */
poly_status poly_value_fits_in_int8(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `int16_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @since 19.0
 */
poly_status poly_value_fits_in_int16(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `int32_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::fitsInInt
 *  @since 19.0
 */
poly_status poly_value_fits_in_int32(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `int64_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @see org::graalvm::polyglot::Value::fitsInLong
 *  @since 19.0
 */
poly_status poly_value_fits_in_int64(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `uint8_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 * 
 *  @since 19.0
 */
poly_status poly_value_fits_in_uint8(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `uint16_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @since 19.0
 */
poly_status poly_value_fits_in_uint16(poly_thread thread, poly_value value, bool* result);

/*
 * Returns `true` if this value is a number and can fit into `uint32_t`.
 * 
 *  @return poly_ok if all works, poly_generic_failure if the underlying context was closed, if guest language error occurred 
 *         during execution.
 *  @since 19.0
 */
poly_status poly_value_fits_in_uint32(poly_thread thread, poly_value value, bool* result);

/*
 * Converts a string value to a C string by filling the <code>buffer</code> with with a string encoded in UTF-8 and 
 * storing the number of written bytes to <code>result</code>. If the the buffer is <code>NULL</code> writes the required
 * size to <code>result</code>.
 * 
 *  @return poly_ok if all works, poly_generic_failure if a guest language error occurred during execution 
 *          poly_string_expected if the value is not a string.
 *  @since 19.0
 */
poly_status poly_value_as_string_utf8(poly_thread thread, poly_value value, char* buffer, size_t buffer_size, size_t* result);

/*
 * Returns a <code>toString</code> representation of a <code>poly_value</code> by filling the <code>buffer</code> with with a string encoded 
 * in UTF-8 and stores the number of written bytes to <code>result</code>. If the the buffer is <code>NULL</code> writes the 
 * required size to <code>result</code>.
 * 
 *  @return poly_ok if all works, poly_generic_failure if a guest language error occurred during execution 
 *          poly_string_expected if the value is not a string.
 *  @since 19.0
 */
poly_status poly_value_to_string_utf8(poly_thread thread, poly_value value, char* buffer, size_t buffer_size, size_t* result);

/*
 * Returns a boolean representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted. 
 *  @see org::graalvm::polyglot::Value::asBoolean
 *  @since 19.0
 */
poly_status poly_value_as_boolean(poly_thread thread, poly_value value, bool* result);

/*
 * Returns a int8_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted. 
 *  @see org::graalvm::polyglot::Value::asByte
 *  @since 19.0
 */
poly_status poly_value_as_int8(poly_thread thread, poly_value value, int8_t* result);

/*
 * Returns a int32_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asInt
 *  @since 19.0
 */
poly_status poly_value_as_int16(poly_thread thread, poly_value value, int16_t* result);

/*
 * Returns a int32_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asInt
 *  @since 19.0
 */
poly_status poly_value_as_int32(poly_thread thread, poly_value value, int32_t* result);

/*
 * Returns a int64_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asInt
 *  @since 19.0
 */
poly_status poly_value_as_int64(poly_thread thread, poly_value value, int64_t* result);

/*
 * Returns a uint8_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asInt
 *  @since 19.0
 */
poly_status poly_value_as_uint8(poly_thread thread, poly_value value, uint8_t* result);

/*
 * Returns a uint16_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *          if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asInt
 *  @since 19.0
 */
poly_status poly_value_as_uint16(poly_thread thread, poly_value value, uint16_t* result);

/*
 * Returns a uint32_t representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *         if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asLong
 *  @since 19.0
 */
poly_status poly_value_as_uint32(poly_thread thread, poly_value value, uint32_t* result);

/*
 * Returns a float representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is null, if a guest language error occurred during execution, 
 *         if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asFloat
 *  @since 19.0
 */
poly_status poly_value_as_float(poly_thread thread, poly_value value, float* result);

/*
 * Returns a double representation of the value.
 * 
 *  @return poly_ok if all works, poly_generic_failure if value is <code>null</code>, if a guest language error occurred during execution, 
 *         if the underlying context was closed, if value could not be converted.
 *  @see org::graalvm::polyglot::Value::asDouble
 *  @since 19.0
 */
poly_status poly_value_as_double(poly_thread thread, poly_value value, double* result);

/*
 * Gets the primary identification string of this language. The language id is
 * used as the primary way of identifying languages in the polyglot API. (eg. <code>js</code>)
 * 
 *  @return a language ID string.
 *  @since 19.0
 */
poly_status poly_language_get_id(poly_thread thread, poly_language language, char* utf8_result, size_t buffer_size, size_t* length);

/*
 * Returns information about last error that occurred on this thread in the poly_extended_error_info structure.
 * 
 * This method must be called right after a failure occurs and can be called only once.
 * 
 *  @return information about the last failure on this thread.
 *  @since 19.0
 */
poly_status poly_get_last_error_info(poly_thread thread, const poly_extended_error_info** result);

/*
 * Creates a polyglot function that calls back into native code.
 * 
 *  @param data user defined data to be passed into the function.
 *  @param callback function that is called from the polyglot engine.
 *  @return information about the last failure on this thread.
 *  @see org::graalvm::polyglot::ProxyExecutable
 *  @since 19.0
 */
poly_status poly_create_function(poly_thread thread, poly_context context, poly_callback callback, void* data, poly_value* value);

/*
 * Retrieves details about the call within a callback (e.g., the arguments from a given callback info).
 * 
 *  @param callback_info from the callback.
 *  @param argc number of arguments to the callback.
 *  @param argv poly_value array of arguments for the callback.
 *  @param the data pointer for the callback.
 *  @since 19.0
 */
poly_status poly_get_callback_info(poly_thread thread, poly_callback_info callback_info, size_t* argc, poly_value* argv, void** data);

/*
 * Raises an exception in a C callback.
 * 
 * Invocation of this method does not interrupt control-flow so it is neccesarry to return from a function after 
 * the exception has been raised. If this method is called multiple times only the last exception will be thrown in
 * in the guest language.
 * 
 *  @param utf8_message 0 terminated error message.
 *  @since 19.0
 */
poly_status poly_throw_exception(poly_thread thread, const char* utf8_message);

/*
 * Deletes a poly_reference. After this point, the reference must not be used anymore.
 * 
 *  @since 19.0
 */
poly_status poly_delete_reference(poly_thread thread, poly_reference reference);

/*
 * Creates a poly_reference from a poly_handle. After this point, the reference is alive until poly_delete_reference is called. 
 * 
 * Handles are: poly_engine, poly_engine_builder, poly_context, poly_context_builder, poly_language, poly_value, 
 * and poly_callback_info.
 * 
 *  @since 19.0
 */
poly_status poly_create_reference(poly_thread thread, poly_handle handle, poly_reference* reference);

/*
 * Opens a handle scope. Until the scope is closed, all objects will belong to the newly created scope.
 * 
 * Handles are: poly_engine, poly_engine_builder, poly_context, poly_context_builder, poly_language, poly_value, 
 * and poly_callback_info.
 * 
 *  @since 19.0
 */
poly_status poly_open_handle_scope(poly_thread thread);

/*
 * Closes a handle scope. After this point, the handles from the current scope must not be used anymore.
 * 
 * Handles are: poly_engine, poly_engine_builder, poly_context, poly_context_builder, poly_language, poly_value, 
 * and poly_callback_info.
 * 
 *  @since 19.0
 */
poly_status poly_close_handle_scope(poly_thread thread);

/*
 * Returns the last exception that occurred on this thread, or does nothing if an exception did not happen.
 * 
 * This method must be called right after an exception occurs (after a method returns poly_pending_exception), 
 * and can be called only once.
 * 
 *  @param result On success, a handle to the last exception on this thread is put here.
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_get_last_exception(poly_thread thread, poly_exception* result);

/*
 * Checks if an exception is caused by a parser or syntax error.
 * 
 *  @param exception Handle to the exception object.
 *  @param result The result of the check.
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_exception_is_syntax_error(poly_thread thread, poly_exception exception, bool* result);

/*
 * Checks if execution has been cancelled.
 * 
 *  @param exception Handle to the exception object.
 *  @param result The result of the check.
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_exception_is_cancelled(poly_thread thread, poly_exception exception, bool* result);

/*
 * Checks if this exception was caused by an internal implementation error.
 * 
 *  @param exception Handle to the exception object.
 *  @param result The result of the check.
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_exception_is_internal_error(poly_thread thread, poly_exception exception, bool* result);

/*
 * Checks if this exception has a guest language exception object attached to it.
 * 
 *  @param exception Handle to the exception object.
 *  @param result The result of the check.
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_exception_has_object(poly_thread thread, poly_exception exception, bool* result);

/*
 * Gets the handle to the guest exception object. This object can then be used in other poly methods.
 * 
 *  @param exception Handle to the exception object.
 *  @param result The handle to the guest object if it exists.
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_exception_get_object(poly_thread thread, poly_exception exception, poly_value* result);

/*
 * Gets the guest stack traces as a string.
 * The returned string is valid until the next call to this function
 * 
 *  @param exception Handle to the exception object.
 *  @param buffer UTF-8 string representing the stack trace. Can be NULL.
 *  @param buffer_size Size of the user-supplied buffer.
 *  @param result If buffer is NULL, this will contain the buffer size required to put the trace string in, otherwise, it will contain the number of bytes written
 *  @return poly_ok if everything went ok, otherwise an error occurred.
 *  @since 19.0
 */
poly_status poly_exception_get_stack_trace(poly_thread thread, poly_exception exception, char* buffer, size_t buffer_size, size_t* result);

#if defined(__cplusplus)
}
#endif
#endif
