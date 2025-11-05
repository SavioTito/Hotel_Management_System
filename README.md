# 🏨 Hotel Management System

A comprehensive C++ console application that demonstrates Object-Oriented Programming principles through a functional hotel management simulation.

## 📋 Project Overview

This system provides a complete hotel management solution with guest registration, room booking, reservation tracking, and billing operations. It serves as an excellent example of how OOP concepts can be applied to solve real-world business problems.

## 🎯 Purpose & Learning Objectives

- Academic Project: End-of-semester presentation demonstrating OOP mastery
- OOP Principles: Practical implementation of key Object-Oriented Programming concepts
- Real-World Application: Simulates actual hotel management workflows
- Code Quality: Single-file architecture for easy presentation and review

## ✨ Features

- **Room Management** - Standard, Deluxe, and Suite rooms with different pricing
- **Guest Registration** - Complete guest profile creation
- **Reservation System** - Book rooms with check-in/check-out dates
- **Cost Calculation** - Automated billing with polymorphic pricing
- **Room Availability** - Real-time availability tracking

## 👥 Guest Services

- Guest Registration: Complete profile creation with unique IDs
- Contact Management: Phone and email storage
- Guest History: Track all registered guests

## 📅 Reservation System

- Booking Management: Create and manage reservations
- Date Handling: Check-in/check-out date tracking
- Automatic Cost Calculation: Dynamic pricing based on room type and duration
- Occupancy Management: Prevent double-booking of rooms

## 💰 Billing & Payments

- Polymorphic Pricing: Different calculation methods per room type
- Transparent Billing: Detailed cost breakdowns
- Service Charges: Additional fees for premium amenities

## OOP Concepts Demonstrated

- **Inheritance**: Room types derived from base `Room` class
- **Polymorphism**: Overridden `calculateCost()` method for different room types
- **Encapsulation**: Private data members with public interfaces
- **Composition**: Hotel class composed of Rooms, Guests, and Reservations

## Quick Start

### Prerequisites
- C++ Compiler (GCC, Clang, or MSVC)
- C++11 or higher support

### Installation and Execution

```bash
git clone https://github.com/SavioTito/Hotel_Management_System
cd hotel-management-system

# Compile the project
g++ -o hotel hotel.cpp

# Run the application
./hotel
