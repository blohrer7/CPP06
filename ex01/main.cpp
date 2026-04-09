/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:47:42 by blohrer           #+#    #+#             */
/*   Updated: 2026/04/09 07:03:48 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int	main(void)
{
	Data		data;
	Data*		originalPtr;
	Data*		deserializedPtr;
	uintptr_t	raw;

	data.id = 42;
	data.name = "Bob";
	data.value = 3.14;

	originalPtr = &data;

	std::cout << "Original pointer:      " << originalPtr << std::endl;
	std::cout << "Original data.id:      " << originalPtr->id << std::endl;
	std::cout << "Original data.name:    " << originalPtr->name << std::endl;
	std::cout << "Original data.value:   " << originalPtr->value << std::endl;

	raw = Serializer::serialize(originalPtr);
	std::cout << "Serialized uintptr_t:  " << raw << std::endl;
	std::cout << "\n";

	deserializedPtr = Serializer::deserialize(raw);

	std::cout << "Deserialized pointer:  " << deserializedPtr << std::endl;
	std::cout << "Deserialized data.id:  " << deserializedPtr->id << std::endl;
	std::cout << "Deserialized data.name:" << deserializedPtr->name << std::endl;
	std::cout << "Deserialized data.value: " << deserializedPtr->value << std::endl;


	return (0);
}
